//
// Created by loren on 08/05/2026.
//

#include <stdio.h>
#include <math.h>
#include "waveform.h"

void analyze_waveform(WaveformSample* data, int total_samples) {
    double sum_squares_A = 0.0, sum_squares_B = 0.0, sum_squares_C = 0.0;

    // tracking the highest and lowest points for all phases (starting with the first row's numbers)
    double max_A = data[0].phase_A_voltage, min_A = data[0].phase_A_voltage;
    double max_B = data[0].phase_B_voltage, min_B = data[0].phase_B_voltage;
    double max_C = data[0].phase_C_voltage, min_C = data[0].phase_C_voltage;

    // looping through every single row of data
    for (int i = 0; i < total_samples; i++) {
        // rms math
        sum_squares_A += (data[i].phase_A_voltage * data[i].phase_A_voltage);
        sum_squares_B += (data[i].phase_B_voltage * data[i].phase_B_voltage);
        sum_squares_C += (data[i].phase_C_voltage * data[i].phase_C_voltage);

        // checking for new max and min values to calculate peak-to-peak later
        if (data[i].phase_A_voltage > max_A) max_A = data[i].phase_A_voltage;
        if (data[i].phase_A_voltage < min_A) min_A = data[i].phase_A_voltage;

        if (data[i].phase_B_voltage > max_B) max_B = data[i].phase_B_voltage;
        if (data[i].phase_B_voltage < min_B) min_B = data[i].phase_B_voltage;

        if (data[i].phase_C_voltage > max_C) max_C = data[i].phase_C_voltage;
        if (data[i].phase_C_voltage < min_C) min_C = data[i].phase_C_voltage;
    }

    double rms_A = sqrt(sum_squares_A / total_samples);
    double rms_B = sqrt(sum_squares_B / total_samples);
    double rms_C = sqrt(sum_squares_C / total_samples);

    // calculating the difference between the absolute highest and lowest peaks
    double ptp_A = max_A - min_A;
    double ptp_B = max_B - min_B;
    double ptp_C = max_C - min_C;

    // printing the results
    printf("Phase A -> RMS: %.2f V | Peak-to-Peak: %.2f V\n", rms_A, ptp_A);
    printf("Phase B -> RMS: %.2f V | Peak-to-Peak: %.2f V\n", rms_B, ptp_B);
    printf("Phase C -> RMS: %.2f V | Peak-to-Peak: %.2f V\n", rms_C, ptp_C);
}