#include "timeMeasurements.h"

double getSerialVersionTime(
    const int nreps,
    const std::string &filename,
    const std::string &outputFilename,
    const int ngram,
    int numStr)
{
    getRandomText(filename, numStr);

    unsigned long long time, resTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        serialVersion::solution(filename, outputFilename, ngram);
        resTime += getMicrosecondsCpuTime() - time;
    }

    return (double)resTime / nreps;
}

double getParallelVersionTime(
    const int nreps,
    const std::string &filename,
    const std::string &outputFilename,
    const int ngram,
    const int numThreads,
    int numStr)
{

    getRandomText(filename, numStr);

    // auto start = std::chrono::high_resolution_clock::now();
    unsigned long long time, resTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        parallelVersion::solution(filename, outputFilename, ngram, numThreads);
        resTime += getMicrosecondsCpuTime() - time;
    }

    // auto end = std::chrono::high_resolution_clock::now();

    // return std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() / nreps;

    return (double)resTime / nreps;
}