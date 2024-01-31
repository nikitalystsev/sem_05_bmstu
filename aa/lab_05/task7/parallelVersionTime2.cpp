#include "../inc/algorithms.h"
#include "../inc/timeMeasurements.h"

#ifndef NMAX
#error where?

#endif
#define N_REPS 1000

int main()
{
    std::locale::global(std::locale(""));

    srand(200);

    std::cout << getParallelVersionTime(
                     N_REPS,
                     "../text1.txt",
                     "../data/output_text1_.txt",
                     3,
                     NMAX,
                     100)
              << std::endl;

    return 0;
}