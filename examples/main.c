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
        printf("CT: %d\n", message->command_type);
        printf("CN: %d\n", message->channel);
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
    uint8_t knob_turn_b[] = {MIDI_CMD_CONTROL + 0xF, 2,  127};
    // pitch bend
    uint8_t pitch_bend[] = {0xE0, 0x00, 0x40};
    // SysEx example
    uint8_t sysex_example[] = {0xF0, 0x43, 0x10, 0x7F, 0x1C, 0x02, 0x30, 0x48, 0x00, 0x00, 0xF7};

    printf("Note on\n");
    test_midi_message(note_on_bytes, 3);
    printf("\n");

    printf("Note off\n");
    test_midi_message(note_off_bytes, 3);
    printf("\n");

    printf("Knob turn, modulation, channel 0\n");
    test_midi_message(knob_turn_a, 3);
    printf("\n");

    printf("Knob turn, breath controller, channel 15\n");
    test_midi_message(knob_turn_b, 3);
    printf("\n");

    printf("Pitch bend\n");
    test_midi_message(pitch_bend, 3);
    printf("\n");

    printf("SysEx\n");
    test_midi_message(sysex_example, 11);
    printf("\n");

    return 0;
}
