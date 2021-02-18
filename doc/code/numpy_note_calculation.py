#!/usr/bin/env python3

"""
A program to calculate note frequencies for a number of MIDI notes.
"""

from numpy import power, divide

def midi_note_to_freq_numpy(keynum):
    return 440.0 * power(2.0, divide((keynum - 69.0), 12.0))

f_numpy = [midi_note_to_freq_numpy(key) for key in range(128)]

print(f_numpy)
