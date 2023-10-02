// c99
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


// Получение времени в миллисекундах
unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
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


#define N    (5 * 1024)


int main(void)
{
    int a[N];
    size_t n = sizeof(a) / sizeof(a[0]);
    long long unsigned beg, end;
    
    srand(time(NULL));
    
    for (size_t i = 0; i < n; i++)
        a[i] = rand();
    
    beg = milliseconds_now();

    sort_bubble(a, n);
    
    end = milliseconds_now();
    
    //print(a, n);
    
    printf("Time %llu\n", end - beg);
    
    return 0;
}
