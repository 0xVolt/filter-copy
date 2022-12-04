#include <bits/stdc++.h>

using namespace std;

int main()
{
    float x = 0, y = 0;

    FILE *plotPipeline = NULL;

    plotPipeline = _popen("gnuplot -persistent", "w");

    fstream plotCommands;
    plotCommands.open("commands.p", ios::in); // open a file to perform read operation using file object
    if (plotCommands.is_open())
    {
        string command;
        while (getline(plotCommands, command))
        {
            // cout << command << endl;
            fprintf(plotPipeline, "%s\n", command);
        }

        plotCommands.close();
    }

    return 0;
}