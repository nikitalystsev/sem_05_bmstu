#include "../inc/memoryMeasurements.h"

#ifndef NMAX
#error where?

#endif

int main(void)
{
    std::cout << calcMemoryDamLevRecCache(NMAX) << std::endl;

    return 0;
}