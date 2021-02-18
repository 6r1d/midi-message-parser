Finding note values
-------------------

If we have the note values cached beforehand, it is a generally faster code.

The question is: "how to find all note values and store them?".


How to calculate a note value?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

I found a code to generate these values at `MusicDSP.org <https://www.musicdsp.org/>`_.
The topic is called `MIDI note / frequency conversion <https://www.musicdsp.org/en/latest/Other/125-midi-note-frequency-conversion.html>`_.

To be precise, I am using a variation of DFL's code:

.. code-block:: C

  double MIDItoFreq( char keynum ) {
    return 440.0 * pow( 2.0, ((double)keynum - 69.0) / 12.0 );
  }

It can also be expressed by a formula,
where :math:`f` is a frequency in Hz and :math:`n` is a `MIDI key number <https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies>`_,
belonging to a range :math:`[0, 127]` and expressed by a single byte:

.. math::

   f = 440 \cdot { 2^{\frac{n-69}{12}} }

This formula returns frequency values for `equal temperament <https://en.wikipedia.org/wiki/Equal_temperament>`_, where the `Middle C <https://en.wikipedia.org/wiki/C_(musical_note)#Middle_C>`_ (MIDI note :math:`\#60`) is C4.

How to ensure we have the correct results?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is an interesting question that is related to a music theory.
If we look at Britannica, we can find an interesting quote about `the octave <https://www.britannica.com/art/octave-music>`_:

    an interval whose higher note has
    a sound-wave frequency of vibration
    twice that of its lower note

We want to see exact frequency values to look for.

   Thus the international standard pitch A above middle C
   vibrates at **440** hertz (cycles per second);
   the octave above this A vibrates at **880** hertz,
   while the octave below it vibrates at **220** hertz

So, we have to look for values like **220**, **440** and **880** where there are intermediate notes between them.

Direct solution
^^^^^^^^^^^^^^^

I propose a little Python program to do just that.

.. literalinclude:: ../code/basic_note_calculation.py
  :language: Python

.. literalinclude:: ../code/basic_note_results.json
  :language: JSON

NumPy solution
^^^^^^^^^^^^^^

There is a possible improvement: use NumPy to do stricter calculations (which aren't giving different results).
Too bad that the result will be exactly the same, but maybe it can be improved later.
The question is, is it needed? I guess I'll return to that later if it is.

.. literalinclude:: ../code/numpy_note_calculation.py
  :language: Python

.. literalinclude:: ../code/numpy_note_results.json
  :language: JSON
