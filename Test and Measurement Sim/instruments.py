#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 6 09:23:57 2026

@author: aliciacunningham
"""

import numpy as np

class Oscilloscope:
    """
    Virtual oscilloscope for waveform capture.
    """

    def __init__(self, sample_rate, noise_std=0.0):
        self.sample_rate = sample_rate
        self.noise_std = noise_std

    def capture(self, signal):
        noise = np.random.normal(0, self.noise_std, size=len(signal))
        return signal + noise