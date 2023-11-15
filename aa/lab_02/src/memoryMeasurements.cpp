#include "memoryMeasurements.h"

using namespace std;

double caclMemAlgClassicMul(const int size)
{
    int resMem = 0;

    resMem += (3 * sizeof(vector<vector<int>>)); // объект вектора
    resMem += (3 * (size * size) * sizeof(int)); // три матрицы
    resMem += (3 * sizeof(int **));              // указатели на матрицы
    resMem += (3 * size * sizeof(int *));        // указатели на строки матриц
    resMem += (3 * sizeof(int));                 // переменные для размеров

    return (double)resMem / 1024;
}

double caclMemAlgVinogradMul(const int size)
{
    int resMem = 0;

    resMem += (3 * sizeof(vector<vector<int>>)); // объект вектора
    resMem += (3 * (size * size) * sizeof(int)); // три матрицы
    resMem += (3 * sizeof(int **));              // указатели на матрицы
    resMem += (3 * size * sizeof(int *));        // указатели на строки матриц
    resMem += (3 * sizeof(int));                 // переменные для размеров
    resMem += (2 * sizeof(vector<int>));         // объект вектора
    resMem += (2 * size * sizeof(int));          // rowFactor и colFactor

    return (double)resMem / 1024;
}

double caclMemAlgVinogradMulWithOpt(const int size)
{
    int resMem = 0;

    resMem += (3 * sizeof(vector<vector<int>>)); // объект вектора
    resMem += (3 * (size * size) * sizeof(int)); // три матрицы
    resMem += (3 * sizeof(int **));              // указатели на матрицы
    resMem += (3 * size * sizeof(int *));        // указатели на строки матриц
    resMem += (3 * sizeof(int));                 // переменные для размеров
    resMem += (2 * sizeof(vector<int>));         // объект вектора
    resMem += (2 * size * sizeof(int));          // rowFactor и colFactor
    resMem += sizeof(int);                       // cCol_half

    return (double)resMem / 1024;
}

double caclMemAlgStrassenMul(const int size)
{
    int resMem = 0;
    int k = static_cast<int>(log2(size)); // степень

    if (!(size && !(size & (size - 1)))) // size не степень 2
        k = ceil(log2(size));

    for (int i = k; i > 2; --i)
    {
        int new_size = pow(2, k) / 2;

        resMem += (3 * sizeof(vector<vector<int>>)); // объект вектора
        resMem += (3 * (size * size) * sizeof(int)); // три матрицы
        resMem += (3 * sizeof(int **));              // указатели на матрицы
        resMem += (3 * size * sizeof(int *));        // указатели на строки матриц
        resMem += (sizeof(int));                     // переменные для размеров

        resMem += (12 * sizeof(vector<vector<int>>));         // объект вектора
        resMem += (12 * (new_size * new_size) * sizeof(int)); // подматрицы
        resMem += (12 * sizeof(int **));                      // указатели на матрицы
        resMem += (12 * new_size * sizeof(int *));            // указатели на строки матриц
        resMem += sizeof(int);                                // переменная для новой размерности

        resMem += (2 * sizeof(vector<vector<int>>));         // объект вектора
        resMem += (2 * (new_size * new_size) * sizeof(int)); // result переменные
        resMem += (2 * sizeof(int **));                      // указатели на матрицы
        resMem += (2 * new_size * sizeof(int *));            // указатели на строки матриц

        resMem += (7 * sizeof(vector<vector<int>>));         // объект вектора
        resMem += (7 * (new_size * new_size) * sizeof(int)); // M_i
        resMem += (7 * sizeof(int **));                      // указатели на матрицы
        resMem += (7 * new_size * sizeof(int *));            // указатели на строки матриц
    }

    return (double)resMem / 1024;
}
