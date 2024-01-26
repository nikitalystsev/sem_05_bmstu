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
                     "../text.txt",
                     "../data/output_text2_.txt",
                     3,
                     NMAX,
                     19)
              << std::endl;

    return 0;
}