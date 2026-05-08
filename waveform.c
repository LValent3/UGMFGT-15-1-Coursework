//
// Created by loren on 08/05/2026.
//

#include <stdio.h>
#include <math.h>
#include "waveform.h"

void analyze_waveform(WaveformSample* data, int total_samples) {
    double sum_squares_A = 0.0, sum_squares_B = 0.0, sum_squares_C = 0.0;
    double sum_A = 0.0, sum_B = 0.0, sum_C = 0.0; // added these for the dc offset bug fix

    // tracking the highest and lowest points for all phases
    double max_A = data[0].phase_A_voltage, min_A = data[0].phase_A_voltage;
    double max_B = data[0].phase_B_voltage, min_B = data[0].phase_B_voltage;
    double max_C = data[0].phase_C_voltage, min_C = data[0].phase_C_voltage;

    // looping through every single row
    for (int i = 0; i < total_samples; i++) {
        // rms math
        sum_squares_A += (data[i].phase_A_voltage * data[i].phase_A_voltage);
        sum_squares_B += (data[i].phase_B_voltage * data[i].phase_B_voltage);
        sum_squares_C += (data[i].phase_C_voltage * data[i].phase_C_voltage);

        // adding up the raw voltages to find the average (dc offset)
        sum_A += data[i].phase_A_voltage;
        sum_B += data[i].phase_B_voltage;
        sum_C += data[i].phase_C_voltage;

        // checking for new max and min values
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

    double ptp_A = max_A - min_A;
    double ptp_B = max_B - min_B;
    double ptp_C = max_C - min_C;

    // calculating the dc offset (just the average of all readings)
    double dc_offset_A = sum_A / total_samples;
    double dc_offset_B = sum_B / total_samples;
    double dc_offset_C = sum_C / total_samples;

    // printing the results so far
    printf("Phase A -> RMS: %.2f V | Pk-Pk: %.2f V | DC Offset: %.2f V\n", rms_A, ptp_A, dc_offset_A);
    printf("Phase B -> RMS: %.2f V | Pk-Pk: %.2f V | DC Offset: %.2f V\n", rms_B, ptp_B, dc_offset_B);
    printf("Phase C -> RMS: %.2f V | Pk-Pk: %.2f V | DC Offset: %.2f V\n", rms_C, ptp_C, dc_offset_C);
}