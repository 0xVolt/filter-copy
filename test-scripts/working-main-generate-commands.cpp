#include "include/FIR.h"

using namespace std;

int main(int argv, char *argc[])
{
    // cout << "Start of main function\n";
    int n = 1000;
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

    // cout << "\n\nDisplaying the generated noisy input:\n";
    // for (int i = 0; i < n; i++) {
    //     cout << input[i] << " ";
    // }

    // cout << "\n\nDisplaying the filtered output:\n";
    // for (int i = 0; i < n; i++) {
    //     cout << filteredInput[i] << " ";
    // }

    // Display a new line for better formatting
    cout << endl;

    // Plotting with GNU Plot
    FILE *gnuplot = fopen("commands.p", "w");
    // FILE *gnuplotData = fopen("data.tmp", "w");
    char gnuPlotCommandString[500] = "";
    char title[200] = "";
    char xLabel[200] = "";
    char yLabel[200] = "";

    // Set the plot title, xlabel and ylabel
    sprintf(title, "Original and filtered samples");
    sprintf(xLabel, "Time");
    sprintf(yLabel, "Amplitude");

    fprintf(gnuplot, "set terminal wxt size 500, 400\n");
    fprintf(gnuplot, "set title '%s'\n", title);
    fprintf(gnuplot, "set xlabel '%s'\n", xLabel);
    fprintf(gnuplot, "set ylabel '%s'\n", yLabel);
    fprintf(gnuplot, "plot \'data.tmp\' title \'Data\'\n");

    // Plot the data
    fprintf(gnuplot, "plot '-' w lines lc rgb 'blue' title \"sampled data\", '-' w lines lc rgb 'red' title \"Filtered data\"\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(gnuplot, "%d %lf\n", i, input[i]);
    }
    fprintf(gnuplot, "e\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(gnuplot, "%d %lf\n", i, filteredInput[i]);
    }
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "replot\n");
    
    // for (int i = 0; i < n; i++)
    // {
    //     fprintf(gnuplotData, "%lf, %lf\n", input[i], filteredInput[i]);
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     fprintf(gnuplotData, "%d %lf\n", i, input[i]);
    // }
    // fprintf(gnuplotData, "e\n");
    // for (int i = 0; i < n; i++)
    // {
    //     fprintf(gnuplotData, "%d %lf\n", i, filteredInput[i]);
    // }
    // fprintf(gnuplotData, "e\n");

    // Close the GNU plot piping
    fclose(gnuplot);
    // fclose(gnuplotData);
    
    // cout << "End of main function\n\n";
    return 0;
}