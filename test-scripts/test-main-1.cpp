#include "include/FIR.h"    //including the FIR filter functions
#include "include/Common.h" //including the FIR filter functions

#include <iostream>

using namespace std;

int main(int argv, char *argc[])
{

    int n = 1000;
    float input[n];
    float filteredInput[n];

    // Generate the input values
    const float pi = 3.14159265358979;
    const float f = 2.5; // Hz
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
    FILE *gnuplot = NULL;

    char gnuPlotCommandString[500] = "";
    char title[200] = "";
    char xLabel[200] = "";
    char yLabel[200] = "";

    // Open the gnuplot for writing/plotting
    sprintf(gnuPlotCommandString, "gnuplot -persistent");
    if ((gnuplot = _popen(gnuPlotCommandString, "w")) == NULL)
    {
        char strError[100];
        sprintf(strError, "Failed to open gnuplot executable");
        printf("[ERROR]: %s\n", strError);
        exit(-1);
    }

    // Set the plot title, xlabel and ylabel
    sprintf(title, "Original and filtered samples");
    sprintf(xLabel, "Time");
    sprintf(yLabel, "Amplitude");

    fprintf(gnuplot, "set terminal %s size 500,400\n", gnuplotTerms[termNo]);
    fprintf(gnuplot, "set title '%s'\n", title);
    fprintf(gnuplot, "set xlabel '%s'\n", xLabel);
    fprintf(gnuplot, "set ylabel '%s'\n", yLabel);

    // Plot the data
    fprintf(gnuplot, "plot '-' w lines lc rgb 'blue' title \"sampled data\", '-' w lines lc rgb 'red' title \"Filtered data\" ");
    for (int i = 0; i < n; i++)
    {
        fprintf(gnuplot, "%d %lf\n", i, input[i]);
    }
    fprintf(gnuplot, "e\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(gnuplot, "%d %lf\n", i, filteredInput[i]);
    }

    // Close the GNU plot piping
    fflush(gnuplot);
    fclose(gnuplot);
}