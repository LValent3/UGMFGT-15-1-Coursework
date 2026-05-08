#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h" // i need this so main knows about the math function

int main(int argc, char *argv[]) {
    // checking if i actually typed a filename in the terminal
    if (argc < 2) {
        printf("Error: Please provide the CSV filename.\n");
        return 1; // exiting the program with an error code
    }

    printf("Starting Power Quality Analyser...\n");
    int total_samples = 0;

    // using argv[1] to open whatever filename i typed in the terminal
    WaveformSample* data = read_csv_data(argv[1], &total_samples);

    // if the data loaded successfully, run the math!
    if (data != NULL) {
        analyze_waveform(data, total_samples);

        // FREEING THE MEMORY! if i forget this, i fail the memory safety requirement
        free(data);
    }

    printf("Program finished successfully.\n");
    return 0;
}