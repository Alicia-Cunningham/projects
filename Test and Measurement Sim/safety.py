#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 6 09:24:00 2026

@author: aliciacunningham
"""

class SafetyMonitor:
    """
    Enforces experiment safety limits.
    """

    def __init__(self, max_voltage, max_current, max_energy):
        self.max_voltage = max_voltage
        self.max_current = max_current
        self.max_energy = max_energy

    def check_limits(self, voltage, current, t):
        energy = (voltage * current).sum() * (t[1] - t[0])

        if voltage.max() > self.max_voltage:
            raise RuntimeError("Voltage safety limit exceeded")

        if current.max() > self.max_current:
            raise RuntimeError("Current safety limit exceeded")

        if energy > self.max_energy:
            raise RuntimeError("Energy safety limit exceeded")