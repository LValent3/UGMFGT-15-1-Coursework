//
// Created by loren on 08/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

WaveformSample* read_csv_data(const char* filename, int* total_samples) {
    // i'm opening the file here to read it
    FILE* file = fopen(filename, "r");

    // this is to check if the file actually exists, otherwise the program will crash
    if (file == NULL) {
        printf("Error: Could not open %s\n", filename);
        return NULL;
    }

    // this is to figure out how many lines are in the file
    int line_count = 0;
    char buffer[1024]; // a temporary space to hold each line as i scan past it

    // looping through the file line by line until there are no lines left
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_count++;
    }

    // subtracting 1 because the top row is just text headers, not actual numbers
    *total_samples = line_count - 1;

    rewind(file);

    // closing it just for now, i will add the memory stuff next
    fclose(file);
    return NULL;
}