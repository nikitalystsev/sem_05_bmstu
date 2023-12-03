#include "timeMeasurements.h"

vector<int> genRandomArr(const int size)
{

    vector<int> arr(size);

    for (int i = 0; i < size; ++i)
        arr[i] = rand(); // Генерируем случайное целое число

    return arr;
}

double getArrSortTime(
    const int nreps,
    ArrSort_t func,
    int size)
{
    vector<int> tmpArr = genRandomArr(size);
    vector<int> arr = tmpArr;

    unsigned long long time, resTime = 0;

    for (int i = 0; i < nreps; ++i)
    {
        time = getMicrosecondsCpuTime();
        func(arr);
        resTime += getMicrosecondsCpuTime() - time;

        arr = tmpArr;
    }

    return (double)resTime / nreps;
}