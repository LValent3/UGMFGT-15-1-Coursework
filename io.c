//
// Created by loren on 08/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

WaveformSample* read_csv_data(const char* filename, int* total_samples) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open %s\n", filename);
        return NULL;
    }

    int line_count = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_count++;
    }

    *total_samples = line_count - 1;
    rewind(file);

    // using malloc to ask for enough memory to hold all the struct rows
    WaveformSample* data = (WaveformSample*)malloc(*total_samples * sizeof(WaveformSample));

    if (data == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // skipping the first line because it's just the text headers
    fgets(buffer, sizeof(buffer), file);

    int i = 0;

    // reading each line and pulling out the 8 comma-separated numbers into my array
    while (fgets(buffer, sizeof(buffer), file) != NULL && i < *total_samples) {
        sscanf(buffer, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &data[i].timestamp,
               &data[i].phase_A_voltage,
               &data[i].phase_B_voltage,
               &data[i].phase_C_voltage,
               &data[i].line_current,
               &data[i].frequency,
               &data[i].power_factor,
               &data[i].thd_percent);
        i++;
    }

    fclose(file);
    return data;
}