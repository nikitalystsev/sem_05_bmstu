#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    printf("Введите размерность векторов: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Размерность векторов должна быть больше нуля.\n");
        return 1; // Возвращаем 1, чтобы показать, что программа завершилась с ошибкой.
    }

    printf("n v = %d\n", n);

    // Объявляем массивы для двух векторов.
    int *vector1 = malloc(n * sizeof(int)), *vector2 = malloc(n * sizeof(int));

    // Заполняем первый вектор.
    printf("Введите элементы первого вектора:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("Элемент 1-го вектора: ");
        scanf("%d", &vector1[i]);
    }

    // Заполняем второй вектор.
    printf("Введите элементы второго вектора:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("Элемент 2-го вектора: ");
        scanf("%d", &vector2[i]);
    }

    // Вычисляем скалярное произведение.
    double scalarProduct = 0.0;
    for (int i = 0; i < n; ++i)
    {
        scalarProduct += vector1[i] * vector2[i];
    }

    printf("Скалярное произведение векторов: %.2lf\n", scalarProduct);

    free(vector1);
    free(vector2);

    return 0; // Возвращаем 0, чтобы показать, что программа завершилась успешно.
}
