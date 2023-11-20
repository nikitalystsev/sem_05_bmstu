#ifndef __TIME_MEASUREMENTS_H__
#define __TIME_MEASUREMENTS_H__

#include <boost/format.hpp>
#include <iostream>

#include "algorithms.h"
#include "colorOutput.h"
#include "processTime.h"

#define N_REPS 1000

using findDist_t = int (*)(const std::wstring &, const std::wstring &);

void timeMeasurement(size_t lenStr, const int nreps, std::array<double, 4> &allTime);

double printAllTimeMeasurement(const size_t lenghtMax);

#endif