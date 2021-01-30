#include <stdbool.h>
#include "midi_parser_constants.h"
#include "midi_mem.h"

#ifndef MIDI_PARSER_MSG_
#define MIDI_PARSER_MSG_

/*
 * @brief A MIDI message.
 */
typedef struct {
    uint8_t  command_type;
    /**< One of the command type constants defined above. */
    uint8_t  channel;
    /**< Channel number for commands that apply to a specific channel (e.g. note on, note off) */
    uint32_t bytes_length;
    /**< The total number of bytes that constitute the message. */

    union data {
        struct midi_note_message {
            uint8_t note;
            double frequency;
            uint8_t velocity;
        } note_message;
        struct midi_cc_message {
            bool decoded;
            bool msb;
            // 64 through 95 are additional single-byte controllers
            // according to the MIDI 1.0 Detailed Specification
            bool is_single_byte;
            uint8_t cc_id;
            uint8_t value;
        } cc_message;
    } cnt;

    uint8_t  bytes[];
    /**< All the bytes that constitute the message (one status byte plus zero or more data bytes). */
} midi_message_t;

/*
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

/*
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

/*
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

/*
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

#ifndef MIDI_GETTYPE
#define MIDI_GETTYPE

/*
 * @brief Returns a `char` array describing a MIDI message type.
 */
const char * get_midi_msg_type(uint8_t command_type)
{
    // Allocate memory for a result string
    char * result = calloc(64, sizeof(char));
    // bit masking using 0b00001111 / 0x0f;
    // incrementing a value, since channels of
    // Expanded MIDI 1.0 Messages List start with 1
    uint8_t midi_channel = midi_channel = command_type & 0x0F;
    // Fill MIDI command name
    switch (command_type) {
        case MIDI_CMD_NOTE_OFF ... MIDI_CMD_NOTE_OFF + 0xF:
            sprintf(result, "NOTE OFF, %d", midi_channel);
            break;
        case MIDI_CMD_NOTE_ON ... MIDI_CMD_NOTE_ON + 0xF:
            sprintf(result, "NOTE ON, %d", midi_channel);
            break;
        case 0xA0 ... 0xAF:
            sprintf(result, "POLYPHONIC AFTERTOUCH, %d", midi_channel);
            break;
        case MIDI_CMD_CONTROL ... MIDI_CMD_CONTROL + 0xF:
            sprintf(result, "CONTROL CHANGE / MODE CHANGE, %d", midi_channel);
            break;
        case MIDI_CMD_PGM_CHANGE ... MIDI_CMD_PGM_CHANGE + 0xF:
            sprintf(result, "PROGRAM CHANGE, %d", midi_channel);
            break;
        case MIDI_CMD_CHANNEL_PRESSURE ... MIDI_CMD_CHANNEL_PRESSURE + 0xF:
            sprintf(result, "AFTERTOUCH, %d", midi_channel);
            break;
        case MIDI_CMD_BENDER ... MIDI_CMD_BENDER + 0xF:
            sprintf(result, "PITCH BEND CHANGE, %d", midi_channel);
            break;
        case 0xF0:
            sprintf(result, "SYSEX START");
            break;
        case 0xF1:
            sprintf(result, "MIDI TIME CODE QTR. FRAME");
            break;
        case 0xF2:
            sprintf(result, "SONG POSITION POINTER");
            break;
        case MIDI_CMD_COMMON_SONG_SELECT:
            sprintf(result, "SONG SELECT / SONG #");
            break;
        case 0xF4:
            sprintf(result, "UNDEFINED / RESERVED");
            break;
        case 0xF5:
            sprintf(result, "UNDEFINED / RESERVED");
            break;
        case MIDI_CMD_COMMON_TUNE_REQUEST:
            sprintf(result, "TUNE REQUEST");
            break;
        case MIDI_CMD_COMMON_SYSEX_END:
            sprintf(result, "SYSEX END");
            break;
        case MIDI_CMD_COMMON_CLOCK:
            sprintf(result, "TIMING CLOCK");
            break;
        case 0xF9:
            sprintf(result, "UNDEFINED / RESERVED");
            break;
        case 0xFA:
            sprintf(result, "START");
            break;
        case MIDI_CMD_COMMON_CONTINUE:
            sprintf(result, "CONTINUE");
            break;
        case MIDI_CMD_COMMON_STOP:
            sprintf(result, "STOP");
            break;
        case 0xFD:
            sprintf(result, "UNDEFINED / RESERVED");
            break;
        case MIDI_CMD_COMMON_SENSING:
            sprintf(result, "ACTIVE SENSING");
            break;
        case MIDI_CMD_COMMON_RESET:
            sprintf(result, "SYSTEM RESET");
            break;
        default:
            sprintf(result, "UNKNOWN VALUE");
    }
    return result;
}

void bytes_to_data(midi_message_t *message) {
    uint8_t cmd_type = message->command_type;
    if (cmd_type >= MIDI_CMD_NOTE_OFF && cmd_type <= MIDI_CMD_NOTE_OFF + 0xF) {
        message->cnt.note_message.note = message->bytes[1];
        message->cnt.note_message.velocity = 0;
        message->cnt.note_message.frequency = NOTE_FREQS[message->bytes[1]];
    }
    if (cmd_type >= MIDI_CMD_NOTE_ON && cmd_type <= MIDI_CMD_NOTE_ON + 0xF) {
        message->cnt.note_message.note = message->bytes[1];
        message->cnt.note_message.velocity = message->bytes[2];
        message->cnt.note_message.frequency = NOTE_FREQS[message->bytes[1]];
    }
    if (cmd_type >= MIDI_CMD_CONTROL && cmd_type <= MIDI_CMD_CONTROL + 0xF) {
        uint8_t cc_type = message->bytes[1];
        // Messages from 0 to 63 can be decoded
        if (cc_type < 64) {
            message->cnt.cc_message.decoded = true;
            message->cnt.cc_message.is_single_byte = false;
            message->cnt.cc_message.msb = cc_type < 32;
            message->cnt.cc_message.cc_id = (cc_type < 32) ?
                cc_type : cc_type - 32;
            message->cnt.cc_message.value = message->bytes[2];
        } else if (cc_type < 95) {
            message->cnt.cc_message.decoded = true;
            message->cnt.cc_message.is_single_byte = true;
            message->cnt.cc_message.msb = true;
            message->cnt.cc_message.cc_id = cmd_type;
            message->cnt.cc_message.value = message->bytes[2];
        } else {
            message->cnt.cc_message.decoded = false;
        }
    }
}
#endif
