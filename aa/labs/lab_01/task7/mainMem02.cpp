#include "../inc/memoryMeasurements.h"

#ifndef NMAX
#error where?

#endif

int main(void)
{
    std::cout << calcMemoryDamLevNotRec(NMAX) << std::endl;

    return 0;
}