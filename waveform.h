//
// Created by loren on 04/05/2026.
//

#ifndef UGMFGT_15_1_COURSEWORK_WAVEFORM_H
#define UGMFGT_15_1_COURSEWORK_WAVEFORM_H

// Struct to hold a single row of data from the CSV file
typedef struct {
    double timestamp;       // Time of sample in seconds
    double phase_A_voltage; // Instantaneous voltage for Phase A
    double phase_B_voltage; // Instantaneous voltage for Phase B
    double phase_C_voltage; // Instantaneous voltage for Phase C
    double line_current;    // Line current magnitude in Amperes
    double frequency;       // Instantaneous frequency in Hz
    double power_factor;    // Ratio of real to apparent power (0-1)
    double thd_percent;     // Total Harmonic Distortion percentage
} WaveformSample;

void analyze_waveform(WaveformSample* data, int total_samples);

#endif //UGMFGT_15_1_COURSEWORK_WAVEFORM_H
