#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int compare(int l, int r)
{
    return l - r;
}


void swap(int *l, int *r)
{
    int tmp = *l;
    
    *l = *r;
    *r = tmp;
}


void sort_bubble(int *a, size_t n)
{
    for (size_t i = 1; i < n; i++)
        for (size_t j = 0; j < n - i; j++)
            if (compare(a[j], a[j + 1]) > 0)
                swap(a + j, a + j + 1);
}


void fill(int *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = rand();
}


void print(const int *a, size_t n)
{
    printf("Array:\n");
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}


#define N         (20 * 1024)


int main(void)
{
    int a[N];
    size_t n = sizeof(a) / sizeof(a[0]);
    
    srand(time(NULL));

    fill(a, n);
    
    sort_bubble(a, n);

    //print(a, n);
    
    return 0;
}
