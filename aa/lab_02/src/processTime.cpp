#include "processTime.h"

unsigned long long getMicrosecondsCpuTime()
{
    struct timespec t;

    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t))
    {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000LL + t.tv_nsec / 1000; // Возвращаем время в микросекундах
}