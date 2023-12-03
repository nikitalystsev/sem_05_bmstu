#include "../inc/memoryMeasurements.h"

#ifndef NMAX
#error where?

#endif

using namespace std;

int main()
{
    cout << calcRadixSortMem(NMAX) << endl;

    return 0;
}