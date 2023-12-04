#ifndef __TIME_MEASUREMENTS_H__
#define __TIME_MEASUREMENTS_H__

#include <iostream>

#include "algorithms.h"
#include "processTime.h"

using namespace std;

#define N_REPS 1000

using ArrSort_t = void (*)(vector<int> &);
using ArrGen_t = vector<int> (*)(const int);

vector<int> genRandomArr(const int size);

vector<int> genAscArr(const int size);

vector<int> genDescArr(const int size);

double getArrSortTime(
    const int nreps,
    ArrSort_t func,
    ArrGen_t func_gen,
    int size);

#endif