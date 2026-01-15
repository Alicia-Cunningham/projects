#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jan 15 09:36:24 2026

@author: aliciacunningham
"""

from test_seq import TestSequence

class Experiment:
    """
    High-level experiment controller.
    """

    def __init__(self, test_sequence, timebase):
        self.test_sequence = test_sequence
        self.timebase = timebase

    def execute(self):
        voltage, current = self.test_sequence.run(self.timebase)
        return voltage, current