#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jan 15 09:24:00 2026

@author: aliciacunningham
"""
import matplotlib.pyplot as plt
import numpy as np

def compute_metrics(voltage, current, t):
    return {
        "peak_voltage": voltage.max(),
        "peak_current": current.max(),
        "pulse_energy": (voltage * current).sum() * (t[1] - t[0])
    }

def plot_waveforms(t, voltage, current):
    plt.figure()
    plt.plot(t * 1e6, voltage, label="Voltage (V)")
    plt.plot(t * 1e6, current, label="Current (A)")
    plt.xlabel("Time (µs)")
    plt.ylabel("Amplitude")
    plt.title("Pulsed Power Transient Response")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def generate_report(metrics, filename="test_report.txt"):
    with open(filename, "w") as f:
        f.write("Pulsed Power Test Report\n")
        f.write("========================\n\n")
        for key, value in metrics.items():
            f.write(f"{key.replace('_',' ').title()}: {value:.3e}\n")