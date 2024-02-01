#include "timeMeasurements.h"

double getParallelVersionTime(
    const int nreps,
    const std::string &filename,
    const std::string &outputFilename,
    const int ngram,
    const int numThreads,
    int numStr)
{

    // getRandomText(filename, numStr);

    unsigned long long time, resTime = 0;

    // for (int i = 0; i < nreps; ++i)
    // {
    //     time = getMicrosecondsCpuTime();
    //     parallelVersion::solution(filename, outputFilename, ngram, numThreads);
    //     resTime += getMicrosecondsCpuTime() - time;
    // }

    return (double)resTime / nreps;
}