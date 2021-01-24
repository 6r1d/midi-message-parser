#include "midi_parser_constants.h"
#include "midi_mem.h"

#ifndef MIDI_PARSER_MSG_
#define MIDI_PARSER_MSG_
/**@brief A MIDI message. */
typedef struct {
    uint8_t  command_type;  /**< One of the command type constants defined above. */
    uint8_t  channel;       /**< Channel number for commands that apply to a specific channel (e.g. note on, note off) */
    uint32_t bytes_length; /**< The total number of bytes that constitute the message. */
    uint8_t  bytes[];      /**< All the bytes that constitute the message (one status byte plus zero or more data bytes). */
} midi_message_t;

/**
* @brief MIDI message constructor
*/
midi_message_t * new_midi_message()
{
    midi_message_t *message = (midi_message_t *) midi_malloc_with_hook(MIDI_MEMORY_CATEGORY, sizeof(midi_message_t));
    message->command_type = 0;
    message->channel = 0;
    message->bytes_length = 0;
    return message;
}

/**
* @brief Deallocates the memory for a midi message.
*/
void free_midi_message(midi_message_t * message)
{
    if (message == NULL)
    {
        return;
    }

    uint32_t size = (uint32_t) sizeof(midi_message_t) + message->bytes_length * sizeof(uint8_t);
    midi_free_with_hook(MIDI_MEMORY_CATEGORY, message, size);
}

/**
* @brief Adds a byte of data to a MIDI message's `bytes` array.
*
* @param[in,out] message_ptr - Pointer to the message into which the byte should be pushed
* @param[in]     byte        - The byte to push into the message's `bytes` array
*/
void add_byte_to_midi_message(midi_message_t **message_ptr, uint8_t byte)
{

    if (message_ptr == NULL || *message_ptr == NULL)
    {
        // This shouldn't happen.
        return;
    }

    midi_message_t *message = *message_ptr;

    size_t prev_size = sizeof(midi_message_t) + message->bytes_length * sizeof(uint8_t);
    message->bytes_length++;
    size_t new_size = prev_size + sizeof(uint8_t);

    // Resize the array of bytes to to have room for the new byte.
    // In order to do this for a struct with a flexible array in standard c, the entire struct needs to be resized.
    *message_ptr = midi_realloc_with_hook(MIDI_MEMORY_CATEGORY, message, new_size, prev_size);
    (*message_ptr)->bytes[(*message_ptr)->bytes_length - 1] = byte;
}

/**
* @brief Appends multiple bytes of data to a MIDI message's `bytes` array.
*
* @param[in,out] message_ptr  - Pointer to the message into which the byte should be pushed
* @param[in]     bytes        - The bytes to push into the message's `bytes` array
* @param[in]     bytes_length - The length of the bytes array.
*/
void add_bytes_to_midi_message(midi_message_t **message_ptr, uint8_t *bytes, uint16_t bytes_length)
{
    if (message_ptr == NULL || *message_ptr == NULL)
    {
        // This shouldn't happen.
        return;
    }

    midi_message_t *message = *message_ptr;

    size_t prev_size = sizeof(midi_message_t) + message->bytes_length;
    size_t new_size = prev_size + bytes_length;

    // Resize the array of bytes to to have room for the new byte.
    // In order to do this for a struct with a flexible array in standard c, the entire struct needs to be resized.
    *message_ptr = midi_realloc_with_hook(MIDI_MEMORY_CATEGORY, message, new_size, prev_size);
    message = *message_ptr;
    memcpy(&message->bytes[message->bytes_length], bytes, bytes_length);
    message->bytes_length += bytes_length;
}
#endif
