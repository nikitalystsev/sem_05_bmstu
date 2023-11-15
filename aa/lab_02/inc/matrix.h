#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

template <typename T>
T **matrix_alloc(const size_t n, const size_t m)
{
    T **mtr = new T *[n];

    if (!mtr)
        return nullptr;

    for (size_t i = 0; i < n; i++)
    {
        mtr[i] = new T[m];

        if (!mtr[i])
        {
            matrix_free<T>(mtr, n);
            return nullptr;
        }
    }

    return mtr;
}

template <typename T>
T **matrix_alloc(const size_t n, const size_t m, const T filler)
{
    T **mtr = new T *[n];

    if (!mtr)
        return nullptr;

    for (size_t i = 0; i < n; i++)
    {
        mtr[i] = new T[m];

        if (!mtr[i])
        {
            matrix_free(mtr, n);
            return nullptr;
        }
    }

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            mtr[i][j] = filler;

    return mtr;
}

template <typename T>
void matrix_free(T **matrix, const size_t n)
{
    for (size_t i = 0; i < n; i++)
        delete[] matrix[i]; // Освобождаем память для элементов в каждой строке

    delete[] matrix; // Освобождаем память для указателей на строки
}

#endif