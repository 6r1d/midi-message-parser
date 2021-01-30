#include <stdio.h>
#include "midi.h"

/*
 * An example that iterates through CC messages, shows it is possible to parse
 * and parses them.
 * TODO: add single-byte message tests;
 * TODO: detailed descriptions.
 */

void test_midi_message(uint8_t * bytes) {
    // Initialize a MIDI parser instance
    midi_message_parser_t * parser = new_midi_message_parser();
    midi_message_t * message;
    // Create an instance for a message
    uint16_t bytes_parsed = 0;
    // Parse a message
    message = parse_midi_message(parser, bytes, 3, &bytes_parsed);
    printf(
        "%d %d %d %d %d\n",
        message->cnt.cc_message.decoded,
        message->cnt.cc_message.is_single_byte,
        message->cnt.cc_message.msb,
        message->cnt.cc_message.cc_id,
        message->cnt.cc_message.value
    );
    // Free a MIDI parser instance
    free(parser);
}

int main(int argc, char *argv[]) {
   const char * name;
   unsigned int value = MIDI_CMD_CONTROL;
   uint8_t message[3]  = {0};
   while (value != MIDI_CMD_CONTROL + 16) {
      message[0] = value;
      name = get_midi_msg_type((uint8_t)value);
      printf("\n%s\n", name);
      for (uint8_t ins_byte=0; ins_byte<64; ins_byte++) {
          message[1] = ins_byte;
          for (uint8_t val_byte = 0; val_byte < 3; val_byte++) {
              message[2] = val_byte;
              test_midi_message(message);
          }
      }
      value++;
   }

   return 0;
}
