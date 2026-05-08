//
// Created by loren on 08/05/2026.
//

#ifndef UGMFGT_15_1_COURSEWORK_IO_H
#define UGMFGT_15_1_COURSEWORK_IO_H

#include "waveform.h"

// Function to read the CSV and give us back the array of data
WaveformSample* read_csv_data(const char* filename, int* total_samples);

// Function to save our math answers later
void write_results_to_file(const char* filename);

#endif //UGMFGT_15_1_COURSEWORK_IO_H