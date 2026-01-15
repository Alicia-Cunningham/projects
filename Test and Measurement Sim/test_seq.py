#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 6 09:23:58 2026

@author: aliciacunningham
"""

class TestSequence:
    """
    Defines the execution flow of an experiment.
    """

    def __init__(self, pulse_source, dut, scope, safety_monitor):
        self.pulse_source = pulse_source
        self.dut = dut
        self.scope = scope
        self.safety_monitor = safety_monitor

    def run(self, t):
        voltage = self.pulse_source.generate_pulse(t)
        current = self.dut.response(voltage, t)

        self.safety_monitor.check_limits(voltage, current, t)

        measured_voltage = self.scope.capture(voltage)
        measured_current = self.scope.capture(current)

        return measured_voltage, measured_current
