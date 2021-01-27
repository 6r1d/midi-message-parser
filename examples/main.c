#include <stdio.h>
#include "midi.h"

void display_midi_message(midi_message_t * message, uint16_t length) {
    for (uint8_t i = 0; i < length; i++) {
        printf("b %d: [0x%02x][%d]\n", i, message->bytes[i], message->bytes[i]);
    }
    printf("\n");
}

void test_midi_message(uint8_t * bytes, uint16_t length) {
    //
    midi_message_parser_t * parser = new_midi_message_parser();
    midi_message_t * message;
    //
    uint16_t bytes_parsed = 0;
    //
    message = parse_midi_message(parser, bytes, length, &bytes_parsed);
    printf("Length: %d\n", length);
    if (message) {
        printf("%d\n", message->command_type);
        display_midi_message(message, length);
    }
    free(parser);
}

int main(int argc, char *argv[]) {
    uint8_t note_on_bytes[]  = {0x90, 64, 64};
    uint8_t note_off_bytes[] = {0x80, 64, 64};
    // 1 - modulation
    uint8_t knob_turn_a[] = {MIDI_CMD_CONTROL, 1,  127};
    // 2 - breath controller
    uint8_t knob_turn_b[] = {MIDI_CMD_CONTROL, 2,  127};

    printf("Note on\n");
    test_midi_message(note_on_bytes, 3);
    printf("\n");

    printf("Note off\n");
    test_midi_message(note_off_bytes, 3);
    printf("\n");

    printf("Knob turn\n");
    test_midi_message(knob_turn_a, 2);
    printf("\n");

    printf("Knob turn (2)\n");
    test_midi_message(knob_turn_b, 2);
    printf("\n");

    return 0;
}
