#include <stdio.h>
#include "midi.h"

void test_midi_message(uint8_t * bytes, uint16_t length) {
    // Initialize a MIDI parser instance
    midi_message_parser_t * parser = new_midi_message_parser();
    midi_message_t * message;
    // Create an instance for a message
    uint16_t bytes_parsed = 0;
    // Parse a message
    message = parse_midi_message(parser, bytes, length, &bytes_parsed);
    // Free a MIDI parser instance
    free(parser);
}

int main(int argc, char *argv[]) {
   const char * name;
   unsigned int value = MIDI_CMD_CONTROL;
   uint8_t instrument_bytes[] = {1, 2, 4, 5, 7, 8, 10, 11, 64, 65, 66, 67, 69, 91, 92, 93, 94, 95};
   uint8_t message[3]  = {0};
   while (value != MIDI_CMD_CONTROL + 16) {
      message[0] = value;
      name = get_midi_msg_type((uint8_t)value);
      printf("%s\n", name);

      for (unsigned int ins_byte_id=0; ins_byte_id<sizeof(instrument_bytes); ins_byte_id++) {
          message[1] = instrument_bytes[ins_byte_id];
          for (unsigned int val_byte=0; val_byte<127; val_byte++) {
              message[2] = (uint8_t)val_byte;
              test_midi_message(message, 3);
          }
      }

      value++;
   }

   return 0;
}
