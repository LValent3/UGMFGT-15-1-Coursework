//
// Created by loren on 08/05/2026.
//
#include <stdio.h>
#include <math.h>
#include "waveform.h"

void analyze_waveform(WaveformSample* data, int total_samples) {
    double sum_squares_A = 0.0, sum_squares_B = 0.0, sum_squares_C = 0.0;
    double sum_A = 0.0, sum_B = 0.0, sum_C = 0.0;

    int clipped_A = 0, clipped_B = 0, clipped_C = 0;

    double max_A = data[0].phase_A_voltage, min_A = data[0].phase_A_voltage;
    double max_B = data[0].phase_B_voltage, min_B = data[0].phase_B_voltage;
    double max_C = data[0].phase_C_voltage, min_C = data[0].phase_C_voltage;

    for (int i = 0; i < total_samples; i++) {
        sum_squares_A += (data[i].phase_A_voltage * data[i].phase_A_voltage);
        sum_squares_B += (data[i].phase_B_voltage * data[i].phase_B_voltage);
        sum_squares_C += (data[i].phase_C_voltage * data[i].phase_C_voltage);

        sum_A += data[i].phase_A_voltage;
        sum_B += data[i].phase_B_voltage;
        sum_C += data[i].phase_C_voltage;

        if (data[i].phase_A_voltage > max_A) max_A = data[i].phase_A_voltage;
        if (data[i].phase_A_voltage < min_A) min_A = data[i].phase_A_voltage;

        if (data[i].phase_B_voltage > max_B) max_B = data[i].phase_B_voltage;
        if (data[i].phase_B_voltage < min_B) min_B = data[i].phase_B_voltage;

        if (data[i].phase_C_voltage > max_C) max_C = data[i].phase_C_voltage;
        if (data[i].phase_C_voltage < min_C) min_C = data[i].phase_C_voltage;

        // updated to the exact 324.9V limit from the brief
        if (fabs(data[i].phase_A_voltage) >= 324.9) clipped_A++;
        if (fabs(data[i].phase_B_voltage) >= 324.9) clipped_B++;
        if (fabs(data[i].phase_C_voltage) >= 324.9) clipped_C++;
    }

    double rms_A = sqrt(sum_squares_A / total_samples);
    double rms_B = sqrt(sum_squares_B / total_samples);
    double rms_C = sqrt(sum_squares_C / total_samples);

    double ptp_A = max_A - min_A;
    double ptp_B = max_B - min_B;
    double ptp_C = max_C - min_C;

    double dc_offset_A = sum_A / total_samples;
    double dc_offset_B = sum_B / total_samples;
    double dc_offset_C = sum_C / total_samples;

    printf("--- Phase A ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d\n", rms_A, ptp_A, dc_offset_A, clipped_A);
    // checking if RMS is within the 207V - 253V tolerance limits
    if (rms_A >= 207.0 && rms_A <= 253.0) printf("Status: Compliant\n"); else printf("Status: OUT OF TOLERANCE\n");

    printf("--- Phase B ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d\n", rms_B, ptp_B, dc_offset_B, clipped_B);
    if (rms_B >= 207.0 && rms_B <= 253.0) printf("Status: Compliant\n"); else printf("Status: OUT OF TOLERANCE\n");

    printf("--- Phase C ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d\n", rms_C, ptp_C, dc_offset_C, clipped_C);
    if (rms_C >= 207.0 && rms_C <= 253.0) printf("Status: Compliant\n"); else printf("Status: OUT OF TOLERANCE\n");
}