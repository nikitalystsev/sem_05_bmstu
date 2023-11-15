#ifndef __TIME_MEASUREMENTS_H__
#define __TIME_MEASUREMENTS_H__

#include <iostream>

#include "algorithms.h"
#include "processTime.h"

using namespace std;

#define N_REPS 1000

using MtrMul_t = vector<vector<int>> (*)(vector<vector<int>> &, vector<vector<int>> &, int, int, int);

vector<vector<int>> genRandomMtr(const int size);

double getMtrMulTime(
    const int nreps,
    MtrMul_t func,
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int size);

#endif