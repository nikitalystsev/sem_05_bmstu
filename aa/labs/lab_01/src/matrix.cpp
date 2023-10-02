#include "matrix.h"

int **matrix_alloc(const size_t n, const size_t m)
{
    int **mtr = static_cast<int **>(calloc(n, sizeof(int *)));

    if (!mtr)
        return nullptr;

    for (size_t i = 0; i < n; i++)
    {
        mtr[i] = static_cast<int *>(calloc(m, sizeof(int)));

        if (!mtr[i])
        {
            matrix_free(mtr, n);
            return nullptr;
        }
    }

    return mtr;
}

int **matrix_alloc(const size_t n, const size_t m, const int filler)
{
    int **mtr = static_cast<int **>(calloc(n, sizeof(int *)));

    if (!mtr)
        return nullptr;

    for (size_t i = 0; i < n; i++)
    {
        mtr[i] = static_cast<int *>(calloc(m, sizeof(int)));

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

void matrix_free(int **matrix, const size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}