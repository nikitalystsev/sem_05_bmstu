#include "../inc/algorithms.h"
#include "../inc/memoryMeasurements.h"

#ifndef NMAX
#error where?

#endif

int main()
{
    std::cout << caclMemAlgVinogradMul(NMAX) << std::endl;

    return 0;
}