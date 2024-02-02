#include "../inc/timeMeasurements.h"

#ifndef NMAX
#error where?

#endif
#define N_REPS 10

int main()
{
    std::locale::global(std::locale(""));

    srand(time(NULL));

    std::cout << getParallelVersionTime(NMAX, 100, 100, 3, N_REPS) << std::endl;

    return 0;
}