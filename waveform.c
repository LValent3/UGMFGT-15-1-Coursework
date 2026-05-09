//
// Created by loren on 08/05/2026.
//
#include <stdio.h>
#include <math.h>
#include <stdint.h> // i need this for the uint8_t bitwise flags
#include "waveform.h"

void analyze_waveform(WaveformSample* data, int total_samples) {
    // --- PASS 1: Find the Average (DC Offset) ---
    double sum_A = 0.0, sum_B = 0.0, sum_C = 0.0;

    for (int i = 0; i < total_samples; i++) {
        sum_A += data[i].phase_A_voltage;
        sum_B += data[i].phase_B_voltage;
        sum_C += data[i].phase_C_voltage;
    }

    double dc_offset_A = sum_A / total_samples;
    double dc_offset_B = sum_B / total_samples;
    double dc_offset_C = sum_C / total_samples;

    // --- PASS 2: Calculate Variance, RMS, Peaks, and Clips ---
    double sum_squares_A = 0.0, sum_squares_B = 0.0, sum_squares_C = 0.0;
    double var_sum_A = 0.0, var_sum_B = 0.0, var_sum_C = 0.0;
    int clipped_A = 0, clipped_B = 0, clipped_C = 0;

    double max_A = data[0].phase_A_voltage, min_A = data[0].phase_A_voltage;
    double max_B = data[0].phase_B_voltage, min_B = data[0].phase_B_voltage;
    double max_C = data[0].phase_C_voltage, min_C = data[0].phase_C_voltage;

    for (int i = 0; i < total_samples; i++) {
        sum_squares_A += (data[i].phase_A_voltage * data[i].phase_A_voltage);
        sum_squares_B += (data[i].phase_B_voltage * data[i].phase_B_voltage);
        sum_squares_C += (data[i].phase_C_voltage * data[i].phase_C_voltage);

        if (data[i].phase_A_voltage > max_A) max_A = data[i].phase_A_voltage;
        if (data[i].phase_A_voltage < min_A) min_A = data[i].phase_A_voltage;
        if (data[i].phase_B_voltage > max_B) max_B = data[i].phase_B_voltage;
        if (data[i].phase_B_voltage < min_B) min_B = data[i].phase_B_voltage;
        if (data[i].phase_C_voltage > max_C) max_C = data[i].phase_C_voltage;
        if (data[i].phase_C_voltage < min_C) min_C = data[i].phase_C_voltage;

        if (fabs(data[i].phase_A_voltage) >= 324.9) clipped_A++;
        if (fabs(data[i].phase_B_voltage) >= 324.9) clipped_B++;
        if (fabs(data[i].phase_C_voltage) >= 324.9) clipped_C++;

        var_sum_A += pow(data[i].phase_A_voltage - dc_offset_A, 2);
        var_sum_B += pow(data[i].phase_B_voltage - dc_offset_B, 2);
        var_sum_C += pow(data[i].phase_C_voltage - dc_offset_C, 2);
    }

    double rms_A = sqrt(sum_squares_A / total_samples);
    double rms_B = sqrt(sum_squares_B / total_samples);
    double rms_C = sqrt(sum_squares_C / total_samples);

    double ptp_A = max_A - min_A;
    double ptp_B = max_B - min_B;
    double ptp_C = max_C - min_C;

    double std_dev_A = sqrt(var_sum_A / total_samples);
    double std_dev_B = sqrt(var_sum_B / total_samples);
    double std_dev_C = sqrt(var_sum_C / total_samples);

    // --- DISTINCTION EXTENSION: Bitwise Status Flags ---
    // bit 0 = clipping, bit 1 = out of tolerance
    uint8_t status_A = 0x00;
    uint8_t status_B = 0x00;
    uint8_t status_C = 0x00;

    // using the bitwise OR operator (|=) and bitshift (<<) to flip the bits
    if (clipped_A > 0) status_A |= (1 << 0);
    if (rms_A < 207.0 || rms_A > 253.0) status_A |= (1 << 1);

    if (clipped_B > 0) status_B |= (1 << 0);
    if (rms_B < 207.0 || rms_B > 253.0) status_B |= (1 << 1);

    if (clipped_C > 0) status_C |= (1 << 0);
    if (rms_C < 207.0 || rms_C > 253.0) status_C |= (1 << 1);

    // printing the answers to the terminal (including the hex status flag)
    printf("\n--- Phase A ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | StdDev: %.2f | Status Flag: 0x%02X\n", rms_A, ptp_A, dc_offset_A, std_dev_A, status_A);
    printf("--- Phase B ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | StdDev: %.2f | Status Flag: 0x%02X\n", rms_B, ptp_B, dc_offset_B, std_dev_B, status_B);
    printf("--- Phase C ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | StdDev: %.2f | Status Flag: 0x%02X\n\n", rms_C, ptp_C, dc_offset_C, std_dev_C, status_C);

    // writing everything to results.txt
    FILE* report = fopen("results.txt", "w");
    if (report != NULL) {
        fprintf(report, "--- Power Quality Report ---\n");
        fprintf(report, "Phase A -> RMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | StdDev: %.2f | Status: 0x%02X\n", rms_A, ptp_A, dc_offset_A, std_dev_A, status_A);
        fprintf(report, "Phase B -> RMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | StdDev: %.2f | Status: 0x%02X\n", rms_B, ptp_B, dc_offset_B, std_dev_B, status_B);
        fprintf(report, "Phase C -> RMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | StdDev: %.2f | Status: 0x%02X\n", rms_C, ptp_C, dc_offset_C, std_dev_C, status_C);
        fclose(report);
        printf("Success: Saved double-Distinction report to results.txt\n");
    } else {
        printf("Error: Could not create results.txt\n");
    }
}