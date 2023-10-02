#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int count = 0;
    double sum = 0;
    double elem;

    if (scanf("%lf", &elem) == 1)
    {
        sum = sum + elem;
        count++;
    }

    while (scanf("%lf", &elem) == 1)
    {
        sum = sum + elem;
        count++;
    }

    printf("%lf", sum / count);

    return EXIT_SUCCESS;
}