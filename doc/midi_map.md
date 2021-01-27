# Possible MIDI commands

Command list table derived from [this one](https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes).
It might be slightly outdated, but seems similars to what VMPK and DAWs send so far.

| Constant                       | C. value | Name                         | Hex range       | Dec range     |
| ------------------------------ | -------- | ---------------------------- | --------------- | ------------- |
| `MIDI_CMD_NOTE_OFF`            | `0x80`   | Note off                     | `0x80` - `0x8F` | `128` - `143` |
| `MIDI_CMD_NOTE_ON`             | `0x90`   | Note on                      | `0x90` - `0x9F` | `144` - `159` |
| `MIDI_CMD_NOTE_PRESSURE`       | `0xA0`   | Polyphonic aftertouch        | `0xA0` - `0xAF` | `160` - `175` |
| `MIDI_CMD_CONTROL`             | `0xB0`   | Control change / mode change | `0xB0` - `0xBF` | `176` - `191` |
| `MIDI_CMD_PGM_CHANGE`          | `0xC0`   | Program change               | `0xC0` - `0xCF` | `192` - `207` |
| `MIDI_CMD_CHANNEL_PRESSURE`    | `0xD0`   | Channel Aftertouch           | `0xD0` - `0xDF` | `208` - `223` |
| `MIDI_CMD_BENDER`              | `0xE0`   | Pitch bend change            | `0xE0` - `0xEF` | `224` - `239` |
| `MIDI_CMD_COMMON_SYSEX`        | `0xF0`   | Sysex start                  | `0xF0`          | `240`         |
| `MIDI_CMD_COMMON_MTC_QUARTER`  | `0xF1`   | MIDI time code qtr. frame    | `0xF1`          | `241`         |
| `MIDI_CMD_COMMON_SONG_POS`     | `0xF2`   | Song position pointer        | `0xF2`          | `242`         |
| `MIDI_CMD_COMMON_SONG_SELECT`  | `0xF3`   | Song select / song number    | `0xF3`          | `243`         |
| `MIDI_CMD_COMMON_TUNE_REQUEST` | `0xF6`   | Tune request                 | `0xF6`          | `246`         |
| `MIDI_CMD_COMMON_SYSEX_END`    | `0xF7`   | SysEx end                    | `0xF7`          | `247`         |
| `MIDI_CMD_COMMON_CLOCK`        | `0xF8`   | Timing clock                 | `0xF8`          | `248`         |
| `MIDI_CMD_COMMON_START`        | `0xFA`   | Start                        | `0xFA`          | `250`         |
| `MIDI_CMD_COMMON_CONTINUE`     | `0xFB`   | Continue                     | `0xFB`          | `251`         |
| `MIDI_CMD_COMMON_STOP`         | `0xFC`   | Stop                         | `0xFC`          | `252`         |
| `MIDI_CMD_COMMON_SENSING`      | `0xFE`   | Active sensing               | `0xFE`          | `254`         |
| `MIDI_CMD_COMMON_RESET`        | `0xFF`   | System reset                 | `0xFF`          | `255`         |
