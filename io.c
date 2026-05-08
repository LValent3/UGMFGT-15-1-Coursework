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

    // checking if the computer actually gave me the memory before moving on
    if (data == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fclose(file);
    return data;
}