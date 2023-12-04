#include "../../../inc/memoryMeasurements.h"

#ifndef NMAX
#error where?

#endif

using namespace std;

int main()
{
    cout << calcBucketSortMem(NMAX) << endl;

    return 0;
}