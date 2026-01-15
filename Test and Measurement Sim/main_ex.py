#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 6 09:31:27 2026

@author: aliciacunningham
"""

import numpy as np
from pulse_source import PulseSource
from dut import DeviceUnderTest
from instruments import Oscilloscope
from safety import SafetyMonitor
from test_seq import TestSequence
from experiment import Experiment
from analysis import compute_metrics, plot_waveforms, generate_report

t = np.linspace(0, 1e-6, 10_000)

pulse = PulseSource(amplitude=1000, pulse_width=5e-7, rise_time=1e-7)
dut = DeviceUnderTest(resistance=50, inductance=1e-6)
scope = Oscilloscope(sample_rate=1e9, noise_std=0.01)
safety = SafetyMonitor(max_voltage=1500, max_current=50, max_energy=1)

sequence = TestSequence(pulse, dut, scope, safety)
experiment = Experiment(sequence, t)

voltage, current = experiment.execute()
metrics = compute_metrics(voltage, current, t)

plot_waveforms(t, voltage, current)
generate_report(metrics)

print(metrics)