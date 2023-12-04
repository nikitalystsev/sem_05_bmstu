#include "../../../../inc/algorithms.h"
#include "../../../../inc/timeMeasurements.h"

#ifndef NMAX
#error where?

#endif
#define N_REPS 1000

using namespace std;

int main()
{
    srand(200);
    cout << getArrSortTime(N_REPS, bucketSort::bucketSort, genAscArr, NMAX) << endl;

    return 0;
}