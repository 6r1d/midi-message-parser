# Description

An example for handling MIDI `Control Change` messages.
It iterates a table of CC message values.
It also runs `parse_midi_message` over each of generated message to check it is handled in a stable way.

# Control Change Values

| Name                   | 2nd byte | 3rd byte    |
| ---------------------- | -------- | ----------- |
| Modulation             | `1`      | `0` - `127` |
| Breath                 | `2`      | `0` - `127` |
| Foot controller        | `4`      | `0` - `127` |
| Portamento time        | `5`      | `0` - `127` |
| Volume                 | `7`      | `0` - `127` |
| Balance                | `8`      | `0` - `127` |
| Pan                    | `10`     | `0` - `127` |
| Expression             | `11`     | `0` - `127` |
| Pedal: Sustain         | `64`     | `0` - `127` |
| Portamento             | `65`     | `0` - `127` |
| Pedal: Sostenuto       | `66`     | `0` - `127` |
| Pedal: Soft            | `67`     | `0` - `127` |
| Hold 2                 | `69`     | `0` - `127` |
| External effects depth | `91`     | `0` - `127` |
| Tremolo depth          | `92`     | `0` - `127` |
| Chorus depth           | `93`     | `0` - `127` |
| Celeste (detune) depth | `94`     | `0` - `127` |
| Phaser depth           | `95`     | `0` - `127` |

# Building

Just type `make`.
