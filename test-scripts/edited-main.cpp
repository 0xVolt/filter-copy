#include "include/FIR.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 20

using namespace std;

int main(int argv, char *argc[])
{
    // cout << "Start of main function\n";
    // cout << "Enter the number of points to generate in the signal: ";
    // cin >> n;

    // Generating noisy data to be filtered
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

    // FIR filter with circular buffer
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

    cout << "\n\nDisplaying the generated noisy input:\n";
    for (int i = 0; i < n; i++) {
        cout << input[i] << " ";
    }

    cout << "\n\nDisplaying the filtered output:\n";
    for (int i = 0; i < n; i++) {
        cout << filteredInput[i] << " ";
    }

    // Display a new line for better formatting
    cout << endl;

    FILE *plotData = fopen("data.tmp", "w");
    FILE *plotPipeline = _popen("gnuplot -persistent", "w");
    
    char *plotCommands[] = {"set title \'Original and filtered samples\'\n", "set xlabel \'Time\'\n", "set ylabel \'Amplitude\'\n", "plot \'data.tmp\' title \'Data\'\n"};

    // vector<string> plotCommands;
    // plotCommands.push_back("set terminal wxt size 500, 400\n");
    // plotCommands.push_back("set title \'Original and filtered samples\'\n");
    // plotCommands.push_back("set xlabel \'Time\'\n");
    // plotCommands.push_back("set ylabel \'Amplitude\'\n");
    // plotCommands.push_back("plot \'data.tmp\' title \'Data\'\n");

    for (int i = 0; i < n; ++i) {
        fprintf(plotData, "%lf %lf\n", input[i], filteredInput[i]);
    }

    for (int i = 0; i < 5; ++i) {
        fprintf(plotPipeline, "%s\n", plotCommands[i]);
    }

    fclose(plotData);
    fclose(plotPipeline);

    // cout << "End of main function\n\n";
    return 0;
}