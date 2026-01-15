#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jan 15 09:23:58 2026

@author: aliciacunningham
"""

import numpy as np

class DeviceUnderTest:
    """
    Represents an electrical load or circuit model.
    """

    def __init__(self, resistance, inductance=0, capacitance=0):
        self.R = resistance
        self.L = inductance
        self.C = capacitance

    def response(self, voltage, t):
        """
        Compute current response to an applied voltage.
        Simplified R / RL / RLC behavior.
        """
        if self.L == 0:
            return voltage / self.R

        # Placeholder RL approximation
        dt = t[1] - t[0]
        current = np.zeros_like(voltage)
        for i in range(1, len(t)):
            current[i] = current[i-1] + (voltage[i] - self.R * current[i-1]) * dt / self.L
        return current