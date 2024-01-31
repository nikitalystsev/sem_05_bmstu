#ifndef __TIME_MEASUREMENTS_H__
#define __TIME_MEASUREMENTS_H__

#include <iostream>

#include "lab_04_code.h"
#include "processTime.h"

double getSerialVersionTime(
    const int nreps,
    const std::string &filename,
    const std::string &outputFilename,
    const int ngram,
    int numStr);

double getParallelVersionTime(
    const int nreps,
    const std::string &filename,
    const std::string &outputFilename,
    const int ngram,
    const int numThreads,
    int numStr);

#endif