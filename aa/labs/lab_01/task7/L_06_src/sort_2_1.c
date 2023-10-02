// gnu11, c17
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
    int rc_beg, rc_end;
    
    {
        rc_beg = timespec_get(&t_beg, TIME_UTC);

        delay(1000);
    
        rc_end = timespec_get(&t_end, TIME_UTC);
        
        if (!rc_beg || !rc_end)
        {
            printf("timespec_get error\n");
            return 1;
        }

        printf("1000 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    {
        rc_beg = timespec_get(&t_beg, TIME_UTC);

        delay(500);
    
        rc_end = timespec_get(&t_end, TIME_UTC);
        
        if (!rc_beg || !rc_end)
        {
            printf("timespec_get error\n");
            return 1;
        }

        printf("500 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    {
        rc_beg = timespec_get(&t_beg, TIME_UTC);

        delay(100);
    
        rc_end = timespec_get(&t_end, TIME_UTC);
        
        if (!rc_beg || !rc_end)
        {
            printf("timespec_get error\n");
            return 1;
        }

        printf("100 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    {
        rc_beg = timespec_get(&t_beg, TIME_UTC);

        delay(50);
    
        rc_end = timespec_get(&t_end, TIME_UTC);
        
        if (!rc_beg || !rc_end)
        {
            printf("timespec_get error\n");
            return 1;
        }

        printf("50 ms %llu\n", calc_elapsed_time(&t_beg, &t_end));
    }
    
    return 0;
}
