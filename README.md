# midi-message-parser

**Important note**: this is not an [official version](https://github.com/BinaryNate/midi-message-parser) of MIDI message parser. It is an experimental fork by [6r1d](https://github.com/6r1d).

A C library for parsing [MIDI (*Musical Instrument Digital Interface*) messages](http://www.gweep.net/~prefect/eng/reference/protocol/midispec.html) from arrays of bytes. This is useful for:

- Parsing discreet messages from an byte array that may contain multiple MIDI messages.
- Parsing long MIDI SysEx messages, which may be sent over many packets.
- Ignoring invalid or malformed MIDI messages.
