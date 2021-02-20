Unused examples
===============

Command tracing
---------------

This example was used to check which MIDI commands belong to which categories. It is currently integrated in the main code, but I decided to save it for the historical reasons.

A command detect_midi_cmd `returns strings <https://stackoverflow.com/questions/1496313/>`_ and is based on an `Expanded MIDI 1.0 Messages List <https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes>`_.

It is currently "translated" to a **get_midi_msg_type** function.

.. literalinclude:: code/cmd_trace.c
  :language: C
