#ifndef MIDI_PARSER_CONSTANTS__
#define MIDI_PARSER_CONSTANTS__

// The category name emitted by this module for memory tracking
#define MIDI_MEMORY_CATEGORY "m"
#define MAXIMUM_LOG_MESSAGE_SIZE 300

/**
* @file Constants for the MIDI command bytes.
*/
#define MIDI_CMD_SND_CTL_NINE           0x4E // 78
#define MIDI_CMD_EFF_FIVE_DEPTH         0x5F // 95
#define MIDI_CMD_NOTE_OFF               0x80
#define MIDI_CMD_NOTE_ON                0x90
#define MIDI_CMD_NOTE_PRESSURE          0xa0
#define MIDI_CMD_CONTROL                0xb0
#define MIDI_CMD_PGM_CHANGE             0xc0
#define MIDI_CMD_CHANNEL_PRESSURE       0xd0
#define MIDI_CMD_BENDER                 0xe0
#define MIDI_CMD_COMMON_SYSEX           0xf0
#define MIDI_CMD_COMMON_MTC_QUARTER     0xf1
#define MIDI_CMD_COMMON_SONG_POS        0xf2
#define MIDI_CMD_COMMON_SONG_SELECT     0xf3
#define MIDI_CMD_COMMON_TUNE_REQUEST    0xf6
#define MIDI_CMD_COMMON_SYSEX_END       0xf7
#define MIDI_CMD_COMMON_CLOCK           0xf8
#define MIDI_CMD_COMMON_START           0xfa
#define MIDI_CMD_COMMON_CONTINUE        0xfb
#define MIDI_CMD_COMMON_STOP            0xfc
#define MIDI_CMD_COMMON_SENSING         0xfe
#define MIDI_CMD_COMMON_RESET           0xff

#ifndef NULL
    #define NULL 0
#endif

/**
* @brief Array containing the constants representing the valid MIDI command types.
*/
const uint8_t MIDI_COMMAND_TYPES[] = {
    MIDI_CMD_SND_CTL_NINE,
    MIDI_CMD_EFF_FIVE_DEPTH,
    //
    MIDI_CMD_NOTE_OFF,
    MIDI_CMD_NOTE_ON,
    MIDI_CMD_NOTE_PRESSURE,
    MIDI_CMD_CONTROL,
    MIDI_CMD_PGM_CHANGE,
    MIDI_CMD_CHANNEL_PRESSURE,
    MIDI_CMD_BENDER,
    MIDI_CMD_COMMON_SYSEX,
    MIDI_CMD_COMMON_MTC_QUARTER,
    MIDI_CMD_COMMON_SONG_POS,
    MIDI_CMD_COMMON_SONG_SELECT,
    MIDI_CMD_COMMON_TUNE_REQUEST,
    // MIDI_CMD_COMMON_SYSEX_END is not included, since no messages start with it.
    MIDI_CMD_COMMON_CLOCK,
    MIDI_CMD_COMMON_START,
    MIDI_CMD_COMMON_CONTINUE,
    MIDI_CMD_COMMON_STOP,
    MIDI_CMD_COMMON_SENSING,
    MIDI_CMD_COMMON_RESET
};
#endif
