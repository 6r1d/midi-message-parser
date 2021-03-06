..
   Code wrapper role to wrap inline commands and so on.
   Think "grave accent inline code on GitHub".

.. role:: cw(code)
   :language: text

MIDI command map
================

Command list table derived from "`Expanded MIDI 1.0 Messages List <https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes>`_".

It might be slightly outdated, but it looks close to what `VMPK <https://vmpk.sourceforge.io/>`_ and `Linux DAWs <https://en.wikipedia.org/wiki/Digital_audio_workstation>`_ send so far. (I know it is a terrible idea to test a standard using existing implementations. I still go with it due to limited time.)

+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| Constant                             | 1st byte     | Name                         | Hex range                 | Dec range     |
+======================================+==============+==============================+===========================+===============+
| :code:`MIDI_CMD_NOTE_OFF`            | :cw:`0x80`   | Note off                     | :cw:`0x80` - :code:`0x8F` | `128` - `143` |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_NOTE_ON`             | :cw:`0x90`   | Note on                      | :cw:`0x90` - :code:`0x9F` | `144` - `159` |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_NOTE_PRESSURE`       | :cw:`0xA0`   | Polyphonic aftertouch        | :cw:`0xA0` - :code:`0xAF` | `160` - `175` |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_CONTROL`             | :cw:`0xB0`   | Control change / mode change | :cw:`0xB0` - :code:`0xBF` | `176` - `191` |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_PGM_CHANGE`          | :cw:`0xC0`   | Program change               | :cw:`0xC0` - :code:`0xCF` | `192` - `207` |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_CHANNEL_PRESSURE`    | :cw:`0xD0`   | Channel Aftertouch           | :cw:`0xD0` - :code:`0xDF` | `208` - `223` |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_BENDER`              | :cw:`0xE0`   | Pitch bend change            | :cw:`0xE0` - :code:`0xEF` | `224` - `239` |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_SYSEX`        | :cw:`0xF0`   | Sysex start                  | :cw:`0xF0`                | `240`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_MTC_QUARTER`  | :cw:`0xF1`   | MIDI time code qtr. frame    | :cw:`0xF1`                | `241`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_SONG_POS`     | :cw:`0xF2`   | Song position pointer        | :cw:`0xF2`                | `242`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_SONG_SELECT`  | :cw:`0xF3`   | Song select / song number    | :cw:`0xF3`                | `243`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_TUNE_REQUEST` | :cw:`0xF6`   | Tune request                 | :cw:`0xF6`                | `246`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_SYSEX_END`    | :cw:`0xF7`   | SysEx end                    | :cw:`0xF7`                | `247`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_CLOCK`        | :cw:`0xF8`   | Timing clock                 | :cw:`0xF8`                | `248`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_START`        | :cw:`0xFA`   | Start                        | :cw:`0xFA`                | `250`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_CONTINUE`     | :cw:`0xFB`   | Continue                     | :cw:`0xFB`                | `251`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_STOP`         | :cw:`0xFC`   | Stop                         | :cw:`0xFC`                | `252`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_SENSING`      | :cw:`0xFE`   | Active sensing               | :cw:`0xFE`                | `254`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
| :code:`MIDI_CMD_COMMON_RESET`        | :cw:`0xFF`   | System reset                 | :cw:`0xFF`                | `255`         |
+--------------------------------------+--------------+------------------------------+---------------------------+---------------+
