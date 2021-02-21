MIDI message parser
===================

.. note::

    This is not an `official version <https://github.com/BinaryNate/midi-message-parser>`_ of MIDI message parser.
    It is an experimental fork by `6r1d <https://github.com/6r1d>`_.
    The API will change from time to time and library will be improving.

.. toctree::
   :maxdepth: 3
   :caption: Contents:

   internals
   plan
   source_doc/main
   examples
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
