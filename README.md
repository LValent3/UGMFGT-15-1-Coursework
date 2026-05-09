# Power Quality Waveform Analyser

This is a C99 command-line tool built to analyse 3-phase industrial power supply data. It reads the raw CSV logs, calculates key electrical metrics such as the RMS, Peak-to-Peak, DC Offset, Clipping, and it evaluates the grid compliance.

## How to Compile and Run (Command Line)
1. Ensure `gcc` is installed on your system.
2. Navigate to the project directory in your terminal.
3. Compile the code using:
   `gcc main.c io.c waveform.c -o analyser -lm -std=c99`
4. Run the program by passing the data file:
   `./analyser power_quality_log.csv`

## How to Run in CLion
1. Open the project in CLion.
2. Edit your Run Configuration (top right corner next to the play button).
3. In the **Program arguments** box, type: `power_quality_log.csv`
4. Ensure the `.csv` file is located in the `cmake-build-debug` folder.
5. Click Run. A `results.txt` file will be generated in the same directory.

**Distinction Features Included:**
* Implemented a two-pass algorithm to calculate signal Variance and Standard Deviation.
* Implemented Bitwise Status Flags (`uint8_t`) to encode the health status of each phase into a single byte.

##Github Repository:
https://github.com/LValent3/UGMFGT-15-1-Coursework