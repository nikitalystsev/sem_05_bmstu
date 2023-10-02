#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

int **matrix_alloc(const size_t n, const size_t m);

int **matrix_alloc(const size_t n, const size_t m, const int filler);

void matrix_free(int **data, const size_t n);

#endif