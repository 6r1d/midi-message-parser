MIDI message parser
===================

.. toctree::
   :maxdepth: 3
   :caption: Contents:

   internals
   plan
   unused_examples
   license

This is a documentation for a MIDI message parser,
a C library that parses
`MIDI <https://en.wikipedia.org/wiki/MIDI>`_ `message <https://www.midi.org/midi-articles/about-midi-part-3-midi-messages>`_ 
bytes and returns MIDI message data.

Uses
----

* parse array of bytes and find `MIDI messages <https://www.midi.org/midi-articles/about-midi-part-3-midi-messages>`_ inside
* get data like pitch from the `MIDI messages <https://www.midi.org/midi-articles/about-midi-part-3-midi-messages>`_
* parse long `SysEx <https://electronicmusic.fandom.com/wiki/System_exclusive>`_ MIDI messages
* ignore invalid or malformed `MIDI messages <https://www.midi.org/midi-articles/about-midi-part-3-midi-messages>`_
