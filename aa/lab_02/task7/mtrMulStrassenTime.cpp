#include "../inc/algorithms.h"
#include "../inc/timeMeasurements.h"

#ifndef NMAX
#error where?

#endif
#define N_REPS 1000

int main()
{
    // Инициализация генератора случайных чисел
    srand(time(NULL));

    vector<vector<int>> mtr1 = genRandomMtr(NMAX);
    vector<vector<int>> mtr2 = genRandomMtr(NMAX);

    vector<vector<int>> res(NMAX, vector<int>(NMAX, 0));

    unsigned long long time, resTime = 0;

    for (int i = 0; i < N_REPS; ++i)
    {
        time = getMicrosecondsCpuTime();
        strassenMul::matrixMulStrassen(mtr1, mtr2, res, NMAX);
        resTime += getMicrosecondsCpuTime() - time;
    }

    std::cout << (double)resTime / N_REPS << std::endl;

    return 0;
}