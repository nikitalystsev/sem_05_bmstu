#include "../inc/algorithms.h"
#include "../inc/memoryMeasurements.h"

#ifndef NMAX
#error where?

#endif

int main()
{
    std::cout << caclMemAlgStrassenMul(NMAX) << std::endl;

    return 0;
}