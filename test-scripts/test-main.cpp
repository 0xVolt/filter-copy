#include "include/FIR.h"    //including the FIR filter functions
#include "include/Common.h" //including the FIR filter functions

#include <iostream>

// Generate the input values
const float pi = 3.14159265358979;
const float f = 2.5;

using namespace std;

int main(int argv, char *argc[])
{

    int n = 1000;
    float input[n];
    float filteredInput[n];

    for (int i = 0; i < n; i++)
    {
        float min = 0.0f;
        float max = 0.3f;
        float noise = min + ((float)rand() / (float)RAND_MAX) * (max - min);
        input[i] = (float)sin(2 * pi * f * i / n) + noise; // one cycle t=i/n=0 to 1
    }

    // Declaring the filter struct variable
    FIRFilter fir;

    // Initialise the filter coefficient (the weight)
    FIRFilter_init(&fir);

    // Calculating the filtered values
    for (int i = 0; i < n; i++)
    {
        FIRFilter_calc(&fir, input[i]);
        filteredInput[i] = fir.out;
    }

    // Plotting with GNU Plot
    FILE *fp = NULL;
    FILE *gnuplotPipeline = NULL;

    char gnuplotCommands[] = {};

    char title[] = {};
    char xLabel[] = {};
    char yLabel[] = {};

    fp = fopen("data.tmp", "w");
    gnuplotPipeline = _popen("gnuplot -persistent", "w");

    // Storing all the values in a temporary file
    for (int i = 0; i < n; ++i) {
        fprintf(fp, "%d %lf\n", i, input[i]);
    }

    // Piping our commands to gnuplot. We've got only two commands, hence i < 2.
    for (int i = 0; i < 2; ++i) {

    } 
    
    // fprintf(fp, "e\n");

    // for (int i = 0; i < n; i++) {
    //     fprintf(fp, "%d %lf\n", i, filteredInput[i]);
    // }

    // Set the plot title, xlabel and ylabel
    // sprintf(title, "Original and filtered samples");
    // sprintf(xLabel, "Time");
    // sprintf(yLabel, "Amplitude");

    // fprintf(gnuplot, "set title '%s'\n", title);
    // fprintf(gnuplot, "set xlabel '%s'\n", xLabel);
    // fprintf(gnuplot, "set ylabel '%s'\n", yLabel);

    // // Plot the data
    // fprintf(gnuplot, "plot '-' w lines lc rgb 'blue' title \"sampled data\", '-' w lines lc rgb 'red' title \"Filtered data\" ");
    // for (int i = 0; i < n; i++)
    // {
    //     fprintf(gnuplot, "%d %lf\n", i, input[i]);
    // }
    // fprintf(gnuplot, "e\n");
    // for (int i = 0; i < n; i++)
    // {
    //     fprintf(gnuplot, "%d %lf\n", i, filteredInput[i]);
    // }

    // Close the GNU plot piping
    fclose(fp);
    fclose(gnuplotPipeline);
}