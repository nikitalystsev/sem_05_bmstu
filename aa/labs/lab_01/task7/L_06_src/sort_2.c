// c11
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


void sort_bubble(int *a, size_t n)
{
    for (size_t i = 1; i < n; i++)
        for (size_t j = 0; j < n - i; j++)
            if (a[j] > a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
}


void print(const int *a, size_t n)
{
    printf("Array:\n");
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}


#define N         (5 * 1024)
#define N_REPS    10


int main(void)
{
    int a[N], src[N];
    size_t n = sizeof(a) / sizeof(a[0]);
    struct timespec t_beg, t_end;
    int rc_beg, rc_end;
    unsigned long long del, sum = 0, max = 0, min = (unsigned long long) -1;
    
    srand(time(NULL));
    
    for (size_t i = 0; i < n; i++)
        src[i] = rand();
    
    // "Разогрев"
    memcpy(a, src, sizeof(src));
    sort_bubble(a, n);
    
    for (int i = 0; i < N_REPS; i++)
    {
        memcpy(a, src, sizeof(src));

        rc_beg = timespec_get(&t_beg, TIME_UTC);

        sort_bubble(a, n);
    
        rc_end = timespec_get(&t_end, TIME_UTC);
        
        if (!rc_beg || !rc_end)
        {
            printf("timespec_get error\n");
            return 1;
        }
        
        del = calc_elapsed_time(&t_beg, &t_end);
    
        sum = sum + del;
        
        if (del > max)
            max = del;
        
        if (del < min)
            min = del;
    }
    
    printf("Time %g (%llu, %llu, %g%%)\n", (double) (sum)/ N_REPS, min, max, (max - min) * 100.0 / max);
    
    return 0;
}
