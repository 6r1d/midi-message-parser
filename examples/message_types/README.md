# Description

This example demonstrates how `get_midi_msg_type` works by iterating through a number of MIDI message types (`128` - `255`).

# TO-DO

- [x] Check if old `name` values are removed. They probably aren't, but I'm not sure about applying `free` to `const char` and GCC complains about it, too. Fixed with [this](https://stackoverflow.com/questions/1496313/) trick.
