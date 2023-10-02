// gnu99
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>


// вычисляет разность времени в микросекундах
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)) / 1000; 
}


// tms - время в милисекундах
int delay(uint32_t tms)
{
    time_t tv_sec = tms / 1000;
    long tv_nsec = (tms % 1000) * 1000000L;
    const struct timespec req = {.tv_sec = tv_sec, .tv_nsec = tv_nsec};
    
    return nanosleep(&req, NULL);
}


int main(void)
{
    struct timespec t_beg, t_end;
    
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        delay(1000);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

        printf("1000 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        delay(500);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

        printf("500 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        delay(100);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

        printf("100 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        delay(50);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

        printf("50 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    return 0;
}
