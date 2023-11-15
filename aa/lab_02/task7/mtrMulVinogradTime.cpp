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

    double resTime = getMtrMulTime(N_REPS, vinogradMul::matrixMulVinograd, mtr1, mtr2, NMAX);

    std::cout << resTime << std::endl;

    return 0;
}