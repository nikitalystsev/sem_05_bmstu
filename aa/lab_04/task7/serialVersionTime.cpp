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

    std::cout << getSerialVersionTime(
                     N_REPS,
                     "../data/text1.txt",
                     "../data/output_text1.txt",
                     3,
                     NMAX)
              << std::endl;

    return 0;
}