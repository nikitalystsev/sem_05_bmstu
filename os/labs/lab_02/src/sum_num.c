#include <stdio.h>

int main()
{
    int n, i;
    float num, sum = 0.0;

    printf("Введите количество чисел: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Количество чисел должно быть больше нуля.\n");
        return 1; // Возвращаем 1, чтобы показать, что программа завершилась с ошибкой.
    }

    printf("n = %d\n", n);

    for (i = 1; i <= n; ++i)
    {
        printf("Введите число: ");
        scanf("%f", &num);
        sum += num;
    }

    printf("Сумма введенных чисел: %.2f\n", sum);

    return 0; // Возвращаем 0, чтобы показать, что программа завершилась успешно.
}