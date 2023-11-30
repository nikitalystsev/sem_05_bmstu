#include "memoryMeasurements.h"

using namespace std;

int calcBucketSortMem(const int size)
{
    int resMem = 0;

    // n, minVal, maxVal, bucketRange, bucketIndex, i, j, index
    resMem += (8 * sizeof(int));
    // переданный вектор
    resMem += sizeof(vector<int>);
    resMem += (size * sizeof(int));
    // матрица блоков (
    resMem += sizeof(vector<vector<int>>);
    resMem += (size * 1 * sizeof(int));

    return resMem;
}

int calcRadixSortMem(const int size)
{
    int resMem = 0;

    // n, i, max, exp -- 2 раза
    resMem += (5 * sizeof(int));
    // output, count
    resMem += (2 * sizeof(vector<int>));
    resMem += (size * sizeof(int));
    resMem += (10 * sizeof(int));
    // переданный вектор
    resMem += sizeof(vector<int>);
    resMem += (size * sizeof(int));

    return resMem;
}

int calcMergeSortMem(const int size)
{
    int resMem = 0;

    int log_n = static_cast<int>(log2(size));

    int c = 2;

    for (int i = 0; i < log_n; ++i)
    {
        // low, high, mid, i, j, k, a, lengthLeft, lengthRight
        resMem += (9 * sizeof(int));
        // arrLeft, arrRight
        resMem += sizeof(vector<int>);
        resMem += ((size / c) * sizeof(int));
        resMem += sizeof(vector<int>);
        resMem += ((size / c) * sizeof(int));

        c *= 2;
    }

    return resMem;
}