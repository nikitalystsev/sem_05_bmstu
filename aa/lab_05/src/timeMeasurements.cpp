#include "timeMeasurements.h"

double getSerialVersionTime(
    const int numAppl,
    const int numLines,
    const int strLenght,
    const int N,
    const int nreps)
{

    unsigned long long time, resTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        serialSolution(numAppl, numLines, strLenght, N);
        resTime += getMicrosecondsCpuTime() - time;
    }

    return (double)resTime / nreps;
}

double getParallelVersionTime(
    const int numAppl,
    const int numLines,
    const int strLenght,
    const int N,
    const int nreps)
{

    unsigned long long time, resTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        conveyorSolution(numAppl, numLines, strLenght, N);
        resTime += getMicrosecondsCpuTime() - time;
    }

    return (double)resTime / nreps;
}