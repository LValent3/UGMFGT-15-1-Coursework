//
// Created by loren on 08/05/2026.
//

#include <stdio.h>
#include <math.h> // i need this for the square root function
#include "waveform.h"

void analyze_waveform(WaveformSample* data, int total_samples) {
    double sum_squares_A = 0.0;
    double sum_squares_B = 0.0;
    double sum_squares_C = 0.0;

    // looping through every single row of data
    for (int i = 0; i < total_samples; i++) {
        // squaring the voltage for all three phases and adding them up
        sum_squares_A += (data[i].phase_A_voltage * data[i].phase_A_voltage);
        sum_squares_B += (data[i].phase_B_voltage * data[i].phase_B_voltage);
        sum_squares_C += (data[i].phase_C_voltage * data[i].phase_C_voltage);
    }

    // calculating the final RMS for all three by dividing by the total and square rooting
    double rms_A = sqrt(sum_squares_A / total_samples);
    double rms_B = sqrt(sum_squares_B / total_samples);
    double rms_C = sqrt(sum_squares_C / total_samples);

    // printing them out just to make sure they look right
    printf("Phase A RMS Voltage: %.2f V\n", rms_A);
    printf("Phase B RMS Voltage: %.2f V\n", rms_B);
    printf("Phase C RMS Voltage: %.2f V\n", rms_C);
}