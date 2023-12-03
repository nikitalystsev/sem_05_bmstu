#ifndef __TIME_MEASUREMENTS_H__
#define __TIME_MEASUREMENTS_H__

#include <iostream>

#include "algorithms.h"
#include "processTime.h"

using namespace std;

#define N_REPS 1000

using ArrSort_t = void (*)(vector<int> &);

vector<int> genRandomArr(const int size);

double getArrSortTime(
    const int nreps,
    ArrSort_t func,
    int size);

#endif