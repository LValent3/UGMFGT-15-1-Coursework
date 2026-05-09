//
// Created by loren on 08/05/2026.
//
#include <stdio.h>
#include <math.h>
#include "waveform.h"

void analyze_waveform(WaveformSample* data, int total_samples) {
    // --- PASS 1: Find the Average (DC Offset) first ---
    double sum_A = 0.0, sum_B = 0.0, sum_C = 0.0;

    // looping through the data for the first time just to get the totals
    for (int i = 0; i < total_samples; i++) {
        sum_A += data[i].phase_A_voltage;
        sum_B += data[i].phase_B_voltage;
        sum_C += data[i].phase_C_voltage;
    }

    // calculating the true average so i can use it in pass 2
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

    // looping through the data a second time to do the complex math
    for (int i = 0; i < total_samples; i++) {
        // rms math
        sum_squares_A += (data[i].phase_A_voltage * data[i].phase_A_voltage);
        sum_squares_B += (data[i].phase_B_voltage * data[i].phase_B_voltage);
        sum_squares_C += (data[i].phase_C_voltage * data[i].phase_C_voltage);

        // checking peaks
        if (data[i].phase_A_voltage > max_A) max_A = data[i].phase_A_voltage;
        if (data[i].phase_A_voltage < min_A) min_A = data[i].phase_A_voltage;
        if (data[i].phase_B_voltage > max_B) max_B = data[i].phase_B_voltage;
        if (data[i].phase_B_voltage < min_B) min_B = data[i].phase_B_voltage;
        if (data[i].phase_C_voltage > max_C) max_C = data[i].phase_C_voltage;
        if (data[i].phase_C_voltage < min_C) min_C = data[i].phase_C_voltage;

        // checking clips
        if (fabs(data[i].phase_A_voltage) >= 324.9) clipped_A++;
        if (fabs(data[i].phase_B_voltage) >= 324.9) clipped_B++;
        if (fabs(data[i].phase_C_voltage) >= 324.9) clipped_C++;

        // variance math: how far is this specific reading from the average?
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

    // final variance and standard deviation calculations
    double variance_A = var_sum_A / total_samples;
    double std_dev_A = sqrt(variance_A);
    double variance_B = var_sum_B / total_samples;
    double std_dev_B = sqrt(variance_B);
    double variance_C = var_sum_C / total_samples;
    double std_dev_C = sqrt(variance_C);

    // printing all the answers to the terminal
    printf("\n--- Phase A ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d | StdDev: %.2f\n", rms_A, ptp_A, dc_offset_A, clipped_A, std_dev_A);
    printf("--- Phase B ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d | StdDev: %.2f\n", rms_B, ptp_B, dc_offset_B, clipped_B, std_dev_B);
    printf("--- Phase C ---\nRMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d | StdDev: %.2f\n\n", rms_C, ptp_C, dc_offset_C, clipped_C, std_dev_C);

    // writing those exact same answers to the text file
    FILE* report = fopen("results.txt", "w");
    if (report != NULL) {
        fprintf(report, "--- Power Quality Report ---\n");
        fprintf(report, "Phase A -> RMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d | StdDev: %.2f\n", rms_A, ptp_A, dc_offset_A, clipped_A, std_dev_A);
        fprintf(report, "Phase B -> RMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d | StdDev: %.2f\n", rms_B, ptp_B, dc_offset_B, clipped_B, std_dev_B);
        fprintf(report, "Phase C -> RMS: %.2f V | Pk-Pk: %.2f V | DC: %.2f V | Clipped: %d | StdDev: %.2f\n", rms_C, ptp_C, dc_offset_C, clipped_C, std_dev_C);
        fclose(report);
        printf("Success: Saved Distinction-level report to results.txt\n");
    } else {
        printf("Error: Could not create results.txt\n");
    }
}