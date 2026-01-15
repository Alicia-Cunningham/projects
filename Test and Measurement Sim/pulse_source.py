#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 6 09:22:57 2026

@author: aliciacunningham
"""


import numpy as np

class PulseSource:
    """
    Simulates a high-voltage pulsed power source.
    """

    def __init__(self, amplitude, pulse_width, rise_time, repetition_rate=1):
        self.amplitude = amplitude
        self.pulse_width = pulse_width
        self.rise_time = rise_time
        self.repetition_rate = repetition_rate

    def generate_pulse(self, t):
        """
        Generate a single voltage pulse waveform.
        """
        pulse = np.zeros_like(t)

        rise_mask = (t >= 0) & (t < self.rise_time)
        flat_mask = (t >= self.rise_time) & (t < self.pulse_width)

        pulse[rise_mask] = (self.amplitude / self.rise_time) * t[rise_mask]
        pulse[flat_mask] = self.amplitude

        return pulse