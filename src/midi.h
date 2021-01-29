#ifndef MIDI_H__
#define MIDI_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "midi_msg.h"
#include "midi_queue.h"
#include "midi_logging.h"
#include "midi_mem.h"
#include "midi_parser_constants.h"

/**
* @brief Enum for the possible states of a pending message being parsed.
*/
typedef enum midi_message_state {
    VALID,   /**< Indicates a complete and valid message that is ready to be used. */
    PENDING, /**< Indicates that the message is not fully received yet. */
    INVALID  /**< Indicates that the message has been fully received but is invalid. */
} midi_message_state_t;

/**@brief Keeps track of pending MIDI messages for which we're still waiting for the remaining bytes. */
typedef struct {
    midi_message_t *_pending_message; /**< Saves a partial message for which the end has not yet been received. */
} midi_message_parser_t;

/**
* @brief Helper function to indicate whether a given byte is a MIDI command byte
*        (i.e. a byte with bit 7 set).
*/
bool is_command_byte(uint8_t byte)
{
    // TODO think how to improve
    // return (0xF0 & byte) >> 7;
    return ((byte > 127) && (byte < 256)) || (byte == 78) || (byte == 95);
}

/**
* @brief MIDI message parser constructor
*/
midi_message_parser_t * new_midi_message_parser()
{
    midi_message_parser_t *parser = (midi_message_parser_t *) midi_malloc_with_hook(MIDI_MEMORY_CATEGORY, sizeof(midi_message_parser_t));
    parser->_pending_message = NULL;
    return parser;
}

/**
* @brief MIDI message parser destructor
*/
void free_midi_message_parser(midi_message_parser_t *parser)
{
    if (!parser)
    {
        return;
    }

    if (parser->_pending_message)
    {
        free_midi_message(parser->_pending_message);
    }
    midi_free_with_hook(MIDI_MEMORY_CATEGORY, parser, sizeof(midi_message_parser_t));
}

/**
* Indicates whether the given MIDI message is valid, invalid, or pending.
*/
static midi_message_state_t validate_midi_message(midi_message_t *message)
{
    if (message == NULL)
    {
        return INVALID;
    }

    if (message->bytes_length < 3)
    {
        return PENDING;
    }

    if (message->command_type == MIDI_CMD_COMMON_SYSEX)
    {
        return message->bytes[message->bytes_length - 1] == MIDI_CMD_COMMON_SYSEX_END ? VALID : PENDING;
    }

    // Allow some of the 3-byte messages
    if (
        message->command_type >= 0x80 &&
        message->command_type <= 0xEF &&
        message->bytes_length == 3
    ) {
        return VALID;
    }

    return INVALID;
}

/**
* @brief Used by the MIDI message constructor to detect whether a given byte is a valid MIDI status byte
*        and, if so, to allocate memory for a new MIDI message instance.
*
* @param[in] status_byte The first byte of the MIDI message, which should be a command byte.
* @return                The new MIDI message if status_byte is a valid MIDI command byte, otherwise NULL.
*/
static midi_message_t * _parse_message_from_status_byte(uint8_t status_byte)
{
    if (!is_command_byte(status_byte))
    {
        return NULL;
    }

    uint8_t number_of_command_types = sizeof(MIDI_COMMAND_TYPES) / sizeof(MIDI_COMMAND_TYPES[0]);
    // invalid, falsy command type
    uint8_t matching_command_type = 0;

    for (uint8_t i = 0; i < number_of_command_types; i++)
    {
        uint8_t command_type = MIDI_COMMAND_TYPES[i];

        if (command_type & 0x0F)
        {
            // This command type is one of the 0xf_ system status types
            // for which the lower nibble does not indicate a channel number.
            // So, let's match the entire command_type code.
            if (command_type == status_byte)
            {
                matching_command_type = command_type;
                break;
            }
        }
        else
        {
            // This command type has a dynamic lower nibble that indicates its channel number,
            // so let's just check that the upper nibble matches.
            if (command_type == (status_byte & 0xF0))
            {
                matching_command_type = command_type;
                break;
            }
        }
    }

    if (matching_command_type)
    {
        // Allocate memory for midi_message_t plus the first byte in the bytes array, which is the status byte.
        midi_message_t * message = (midi_message_t *) midi_malloc_with_hook(MIDI_MEMORY_CATEGORY, sizeof(midi_message_t) + sizeof(uint8_t));

        message->bytes_length = 1;
        // The lower nibble indicates the channel number except on the 0xF_ system status commands.
        message->bytes[0] = status_byte;
        message->command_type = matching_command_type;

        // Only set the channel for non-system messages.
        bool is_system_message = (0xF0 & status_byte) == 0xF0;
        message->channel = is_system_message ? 0 : (status_byte & 0x0F);
        return message;
    }

    return NULL;
}

/**
* @brief Given an array of bytes that may contain one or more MIDI messages
*        it will construct the midi_message_t instance from the first MIDI message in the array it
*        encounters. If it doesn't encounter any MIDI messages in the array, it returns NULL.
*
* @param[in]  parser                 - Message parser that keeps track of unfinished messages for which the final bites have yet to be received.
* @param[in]  bytes                  - The message bytes to parse
* @param[in]  length                 - Length of the message byte buffer
* @param[out] number_of_bytes_parsed - The number of bytes parsed
*/
midi_message_t * parse_midi_message(midi_message_parser_t *parser, uint8_t *bytes, uint16_t length, uint16_t *number_of_bytes_parsed)
{
    for (uint16_t byte_index = 0; byte_index < length; byte_index++)
    {
        uint8_t byte = bytes[byte_index];

        if (is_command_byte(byte) && byte != MIDI_CMD_COMMON_SYSEX_END)
        {
            if (parser->_pending_message != NULL)
            {
                free_midi_message(parser->_pending_message);
            }

            parser->_pending_message = _parse_message_from_status_byte(byte);
            continue;
        }

        // `byte` is a data byte or a MIDI SysEx End command byte
        if (parser->_pending_message == NULL) {
            midi_log_info("Ignoring data byte %x, because there is no pending MIDI message.", byte);
            continue;
        }

        add_byte_to_midi_message(&(parser->_pending_message), byte);

        midi_message_state_t state = validate_midi_message(parser->_pending_message);

        switch (state)
        {
            case VALID:
            {
                bytes_to_data(parser->_pending_message);
                // Brackets needed to create a scope for the local var.
                midi_message_t *complete_message = parser->_pending_message;
                parser->_pending_message = NULL;
                *number_of_bytes_parsed = byte_index + 1;
                return complete_message;
            }
            case INVALID:
                free_midi_message(parser->_pending_message);
                parser->_pending_message = NULL;
                break;
            case PENDING:
                // In the case where the message is PENDING, just continue processing bytes.
                break;
        }
    }
    // A complete, valid message wasn't parsed, so return null.
    *number_of_bytes_parsed = length;
    return NULL;
}

/**
* @brief Converts a raw array of bytes (presumably received from another MIDI host) to a queue of MIDI messages.
*
* @param[in] parser - Keeps track of partially received messages for which we're still waiting for the remaining bytes.
* @param[in] bytes  - The array of raw bytes receive that presumably contains one or more MIDI messages.
* @return           - A queue containing all of the MIDI messages parsed from the bytes array.
*/
midi_message_queue_t * parse_midi_messages(midi_message_parser_t *parser, uint8_t *bytes, uint16_t bytes_length)
{
    midi_log_info("Parsing raw bytes into MIDI messages...");

    midi_message_queue_t * message_queue = new_midi_message_queue();
    uint16_t byte_index = 0;

    // Keep feeding bytes into the MIDI message constructor, each time offsetting the array
    // by the amount that it had bitten off to create the previous message.
    while (byte_index < bytes_length)
    {
        uint8_t * offset_bytes = &bytes[byte_index];
        uint16_t offset_bytes_length = bytes_length - byte_index;
        uint16_t number_of_bytes_parsed;

        midi_message_t * message = parse_midi_message(parser, offset_bytes, offset_bytes_length, &number_of_bytes_parsed);

        if (!message)
        {
            // No more valid messages left in the bytes array, so our work here is already done.
            break;
        }

        midi_log_info("Pushing new MIDI message into queue: ");
        midi_log_bytes(message->bytes, message->bytes_length);

        add_midi_message_to_queue(&message_queue, message);
        byte_index += number_of_bytes_parsed;
    }

    midi_log_info("Finished parsing raw bytes into MIDI messages...");

    return message_queue;
}
#endif // MIDI_H__

