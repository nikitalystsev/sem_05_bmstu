#include "../inc/memoryMeasurements.h"

#ifndef NMAX
#error where?

#endif

int main(void)
{
    std::cout << calcMemoryDamLevRec(NMAX) << std::endl;

    return 0;
}