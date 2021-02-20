#include <stdio.h>
#include <stdint.h>

/* 0x80 - 0x8F; 128 - 143 - note off */
#define MIDI_CMD_NOTE_OFF               0x80
/* 0x90 - 0x9F; 144 - 159 - note on */
#define MIDI_CMD_NOTE_ON                0x90
/* 0xA0 - 0xAF; 160 - 175 - polyphonic aftertouch */
#define MIDI_CMD_NOTE_PRESSURE          0xa0
/* 0xB0 - 0xBF; 176 - 191 - control change / mode change */
#define MIDI_CMD_CONTROL                0xb0
/* 0xC0 - 0xCF; 192 - 207 - program change */
#define MIDI_CMD_PGM_CHANGE             0xc0
/* 0xD0 - 0xDF; 208 - 223 - aftertouch */
#define MIDI_CMD_CHANNEL_PRESSURE       0xd0
/* 0xE0 - 0xEF; 224 - 239 - pitch bend change */
#define MIDI_CMD_BENDER                 0xe0
/* 0xF0; 240 - sysex start */
#define MIDI_CMD_COMMON_SYSEX           0xf0
/* 0xF1; 241 - midi time code qtr. frame */
#define MIDI_CMD_COMMON_MTC_QUARTER     0xf1
/* 0xF2; 242 - song position pointer */
#define MIDI_CMD_COMMON_SONG_POS        0xf2
/* 0xF3; 243 - song select / song # */
#define MIDI_CMD_COMMON_SONG_SELECT     0xf3
/* 0xF6; 246 - tune request */
#define MIDI_CMD_COMMON_TUNE_REQUEST    0xf6
/* 0xF7; 247 - sysex end */
#define MIDI_CMD_COMMON_SYSEX_END       0xf7
/* 0xF8; 248 - timing clock */
#define MIDI_CMD_COMMON_CLOCK           0xf8
/* 0xFA; 250 - start */
#define MIDI_CMD_COMMON_START           0xfa
/* 0xFB; 251 - continue */
#define MIDI_CMD_COMMON_CONTINUE        0xfb
/* 0xFC; 252 - stop */
#define MIDI_CMD_COMMON_STOP            0xfc
/* 0xFE; 254 - active sensing */
#define MIDI_CMD_COMMON_SENSING         0xfe
/* 0xFF; 255 - system reset */
#define MIDI_CMD_COMMON_RESET           0xff

/* 0xF4; 244 - undefined / reserved */
/* 0xF5; 245 - undefined / reserved */
/* 0xF9; 249 - undefined / reserved */
/* 0xFD; 253 - undefined / reserved */

void detect_midi_cmd(uint8_t command_type) {
    // bit masking using 0b00001111 / 0x0f;
    // incrementing a value, since channels of
    // the command list start with 1
    uint8_t midi_channel = midi_channel = (command_type & 0x0f) + 1;
    switch (command_type) {
        case MIDI_CMD_NOTE_OFF ... MIDI_CMD_NOTE_OFF + 0xF:
            printf("NOTE OFF, %d", midi_channel);
            break;
        case MIDI_CMD_NOTE_ON ... MIDI_CMD_NOTE_ON + 0xF:
            printf("NOTE ON, %d", midi_channel);
            break;
        case 0xA0 ... 0xAF:
            printf("POLYPHONIC AFTERTOUCH, %d", midi_channel);
            break;
        case MIDI_CMD_CONTROL ... MIDI_CMD_CONTROL + 0xF:
            printf("CONTROL CHANGE / MODE CHANGE, %d", midi_channel);
            break;
        case MIDI_CMD_PGM_CHANGE ... MIDI_CMD_PGM_CHANGE + 0xF:
            printf("PROGRAM CHANGE, %d", midi_channel);
            break;
        case MIDI_CMD_CHANNEL_PRESSURE ... MIDI_CMD_CHANNEL_PRESSURE + 0xF:
            printf("AFTERTOUCH, %d", midi_channel);
            break;
        case MIDI_CMD_BENDER ... MIDI_CMD_BENDER + 0xF:
            printf("PITCH BEND CHANGE, %d", midi_channel);
            break;        
        case 0xF0:
            printf("SYSEX START");
            break;
        case 0xF1:
            printf("MIDI TIME CODE QTR. FRAME");
            break;
        case 0xF2:
            printf("SONG POSITION POINTER");
            break;
        case MIDI_CMD_COMMON_SONG_SELECT:
            printf("SONG SELECT / SONG #");
            break;
        case 0xF4:
            printf("UNDEFINED / RESERVED");
            break;
        case 0xF5:
            printf("UNDEFINED / RESERVED");
            break;
        case MIDI_CMD_COMMON_TUNE_REQUEST:
            printf("TUNE REQUEST");
            break;
        case MIDI_CMD_COMMON_SYSEX_END:
            printf("SYSEX END");
            break;
        case MIDI_CMD_COMMON_CLOCK:
            printf("TIMING CLOCK");
            break;
        case 0xF9:
            printf("UNDEFINED / RESERVED");
            break;
        case 0xFA:
            printf("START");
            break;
        case MIDI_CMD_COMMON_CONTINUE:
            printf("CONTINUE");
            break;
        case MIDI_CMD_COMMON_STOP:
            printf("STOP");
            break;
        case 0xFD:
            printf("UNDEFINED / RESERVED");
            break;
        case MIDI_CMD_COMMON_SENSING:
            printf("ACTIVE SENSING");
            break;
        case MIDI_CMD_COMMON_RESET:
            printf("SYSTEM RESET");
            break;
        default:
            printf("UNKNOWN VALUE");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
   uint8_t value = 128;
   while (value != 0) {
      detect_midi_cmd(value);
      value++;
   }

   return 0;
}
