#!/usr/bin/env python3

"""
A program to calculate note frequencies for a number of MIDI notes.
"""

from numpy import power, divide

def midi_note_to_freq_basic(keynum):
    return 440.0 * pow(2.0, (keynum - 69.0) / 12.0)

f_basic = [midi_note_to_freq_basic(key) for key in range(128)]

print(f_basic)
