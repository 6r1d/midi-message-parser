#include <stdio.h>
#include "midi.h"

/*
 * An example that iterates through CC messages, shows it is possible to parse
 * and parses them.
 * 
 * CC ID for instruments < 64 will always belong to 0/32, because second byte carries other value byte.
 *
 * TODO: add single-byte message tests;
 */

#define CC_MIN MIDI_CMD_CONTROL
// MIDI_CMD_CONTROL + 16 is a maximum CC message value
#define CC_MAX MIDI_CMD_CONTROL + 16

void test_midi_message(uint8_t * bytes) {
    // Initialize a MIDI parser instance
    midi_message_parser_t * parser = new_midi_message_parser();
    midi_message_t * message;
    // Create an instance for a message
    uint16_t bytes_parsed = 0;
    const char * name = get_midi_msg_type(bytes[0]);
    const char * carried_byte;
    printf("%s\n", name);
    // Parse a message
    message = parse_midi_message(parser, bytes, 3, &bytes_parsed);
    if (message->cnt.cc_message.decoded) {
        printf("Message was decoded.\n");
        printf("Singlebyte? %d\n", message->cnt.cc_message.is_single_byte);
        carried_byte = (message->cnt.cc_message.msb) ? "MSB" : "LSB";
        printf("Message carries %s value.\n", carried_byte);
        printf("CC id (0 - 31): %d.\n", message->cnt.cc_message.cc_id);
        printf("CC range (0 - 3): %d.\n", message->cnt.cc_message.cc_range);
        printf("CC value: %d\n", message->cnt.cc_message.value);
    } else {
        printf("Message was not decoded.\n");
    }
    printf("\n");
    // Free a MIDI parser instance
    free(parser);
}

void test_message_range(unsigned int cc_start, unsigned int cc_stop, uint8_t ins_min, uint8_t ins_max) {
    // 1st byte of a MIDI message, determining a command
    // (always CC for the example) and a channel
    unsigned int cmd_byte;
    // Message container, contains three zero bytes
    uint8_t message[3]  = {0};
    // Iterate through CC values and parse them
    for (cmd_byte = cc_start; cmd_byte <= cc_stop; cmd_byte++) {
        message[0] = cmd_byte;
        // Iterate through CC instruction bytes
        for (uint8_t ins_byte = ins_min; ins_byte <= ins_max; ins_byte++) {
            message[1] = ins_byte;
            // Iterate through the values
            for (uint8_t val_byte = 0; val_byte < 3; val_byte++) {
                message[2] = val_byte;
                test_midi_message(message);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    test_message_range(CC_MIN, CC_MIN + 1, 0, 63);

    return 0;
}
