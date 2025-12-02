#include <iostream>
#include "../include/Simulation.h"

using namespace std;

int main()
{
    Simulation simulation;

    if (!simulation.loadInputFile("/dev/stdin"))
    {
        cerr << "Error loading input file. Program will exit." << endl;
        return 1;
    }

    simulation.initialize();

    simulation.run();

    return 0;
}
