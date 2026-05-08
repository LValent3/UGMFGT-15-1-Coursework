//
// Created by loren on 08/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

WaveformSample* read_csv_data(const char* filename, int* total_samples) {
    // i'm opening the file here just to read it
    FILE* file = fopen(filename, "r");

    // check if the file actually exists, otherwise program will crash
    if (file == NULL) {
        printf("Error: Could not open %s\n", filename);
        return NULL;
    }

    printf("Success! Found and opened %s\n", filename);

    // closing it just for now, i will add the memory stuff next
    fclose(file);
    return NULL;
}