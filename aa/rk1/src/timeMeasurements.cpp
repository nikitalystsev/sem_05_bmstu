#include "timeMeasurements.h"

double getSerialVersionTime(
    const int numAppl,
    const int numLines,
    const int strLenght,
    const int N,
    const int nreps)
{

    unsigned long long time, resTime = 0;
    unsigned long long workTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        workTime += serialSolution(numAppl, numLines, strLenght, N);
        resTime += getMicrosecondsCpuTime() - time;
    }

    workTime /= 1000;

    return (double)workTime / nreps;
}

double getParallelVersionTime(
    const int numAppl,
    const int numLines,
    const int strLenght,
    const int N,
    const int nreps)
{

    unsigned long long time, resTime = 0;
    unsigned long long workTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        workTime += conveyorSolution(numAppl, numLines, strLenght, N);
        resTime += getMicrosecondsCpuTime() - time;
    }

    workTime /= 1000;

    return (double)workTime / nreps;
}