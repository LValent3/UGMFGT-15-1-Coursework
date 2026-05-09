# Power Quality Waveform Analyser

This is a C99 command-line tool built to analyse 3-phase industrial power supply data. It reads raw CSV logs, calculates key electrical metrics (RMS, Peak-to-Peak, DC Offset, Clipping), and evaluates grid compliance.

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