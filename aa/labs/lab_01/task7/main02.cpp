#include "../inc/timeMeasurements.h"

#ifndef NMAX
#error where?

#endif
#define N_REPS_ 1000

int main(void)
{
    srand(time(NULL));

    std::array<double, 4> allTime = {};

    timeMeasurement(NMAX, N_REPS_, allTime);

    std::cout << allTime[1] << std::endl;

    return 0;
}