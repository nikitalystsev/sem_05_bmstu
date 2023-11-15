#include "timeMeasurements.h"

vector<vector<int>> genRandomMtr(const int size)
{

    vector<vector<int>> matrix(size, vector<int>(size, 0));

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i][j] = rand(); // Генерируем случайное целое число

    return matrix;
}

double getMtrMulTime(
    const int nreps,
    MtrMul_t func,
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int size)
{
    unsigned long long time, resTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        vector<vector<int>> res = func(mtr1, mtr2, size, size, size);
        resTime += getMicrosecondsCpuTime() - time;
    }

    return (double)resTime / nreps;
}