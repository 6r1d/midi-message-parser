Examples
========

.. toctree::
   :maxdepth: 3
   :caption: Contents:

   unused_examples

main
----

Parses a number of example inputs:

* Note on
* Note off
* Knob turn
* Pitch bend
* SysEx

cc test
-------

Iterates through a number of MIDI Control Change commands with different values for each commands.
It is useful to test if each command was parsed or not.

CC commands are divided to LSB (least single byte) and MSB (most single byte) values.
Range for **MSB** and **LSB** is :math:`[0, 127]`: only 7 bits are used.

**111 1111** = **0x7F** = **0d127**

According to `MIDI 1.0 detailed specification <https://www.midi.org/specifications-old/item/the-midi-1-0-specification>`_ (page **12**),

  When an **MSB** is received, the receiver should set its concept of the **LSB** to zero.

So, **MSB CC message** clearly resets **LSB** to zero.

Also:

  If 128 steps of resolution is sufficient the second byte (**LSB**) of the data value can be omitted.

  If both the **MSB** and **LSB** are sent initially, a subsequent fine adjustment only requires the sending of the **LSB**.
  The **MSB** does not have to be retransmitted.
  If a subsequent major adjustment is necessary the **MSB** must be transmitted again.

Output format:

.. code-block:: none

  CONTROL CHANGE / MODE CHANGE, 1
  Message was decoded.
  Singlebyte? 0
  Message carries LSB value.
  CC id (0 - 31): 31.
  CC range (0 - 3): 0.
  CC value: 2

message types
-------------

Demonstrates how **get_midi_msg_type** works by iterating through a number of MIDI message types :math:`[128, 255]`.
