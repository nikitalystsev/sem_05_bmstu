#include "../../../../inc/algorithms.h"
#include "../../../../inc/timeMeasurements.h"

#ifndef NMAX
#error where?

#endif

#ifndef STATE
#error where?

#endif

#define N_REPS 1000

using namespace std;

int main()
{
    srand(STATE);
    cout << getArrSortTime(N_REPS, bucketSort::bucketSort, genRandomArr, NMAX) << endl;

    return 0;
}