//
// Created by loren on 08/05/2026.
//

#include <stdio.h>
#include <math.h> // i need this for the square root function
#include "waveform.h"

void analyze_waveform(WaveformSample* data, int total_samples) {
    double sum_squares_A = 0.0;

    // looping through every single row of data
    for (int i = 0; i < total_samples; i++) {
        // squaring the voltage and adding it to my running total
        sum_squares_A += (data[i].phase_A_voltage * data[i].phase_A_voltage);
    }

    // calculating the final RMS by dividing by the total and square rooting
    double rms_A = sqrt(sum_squares_A / total_samples);

    // printing it out just to make sure it looks like a real voltage
    printf("Phase A RMS Voltage: %.2f V\n", rms_A);
}