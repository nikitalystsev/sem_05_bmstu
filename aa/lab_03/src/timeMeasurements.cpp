#include "timeMeasurements.h"

vector<int> genRandomArr(const int size)
{

    vector<int> arr(size);

    for (int i = 0; i < size; ++i)
        arr[i] = rand(); // Генерируем случайное целое число

    return arr;
}

vector<int> genAscArr(const int size)
{

    vector<int> arr(size);

    for (int i = 0; i < size; ++i)
        arr[i] = rand(); // Генерируем случайное целое число

    std::sort(arr.begin(), arr.end());

    return arr;
}

vector<int> genDescArr(const int size)
{
    vector<int> arr(size);

    for (int i = 0; i < size; ++i)
        arr[i] = rand(); // Генерируем случайное целое число

    // Сортируем в убывающем порядке
    std::sort(arr.rbegin(), arr.rend());

    return arr;
}

double getArrSortTime(
    const int nreps,
    ArrSort_t func,
    ArrGen_t func_gen,
    int size)
{
    vector<int> tmpArr = func_gen(size);
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