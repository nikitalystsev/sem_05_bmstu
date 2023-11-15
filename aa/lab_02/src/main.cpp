#include <stdio.h>

#include "algorithms.h"

using namespace std;

void printMatrix(const vector<vector<int>> &matrix)
{
    for (const vector<int> &row : matrix)
    {
        for (int element : row)
            cout << element << "\t"; // Используйте "\t" для разделения элементов
        cout << endl;                // Переход на новую строку после каждой строки матрицы
    }
}

int main()
{
    // vector<vector<int>> a(3, vector<int>(4, 0)), b(4, vector<int>(5, 0));

    // for (int i = 0; i < 3; ++i)
    //     for (int j = 0; j < 4; ++j)
    //         a[i][j] = i + j;

    // for (int i = 0; i < 4; ++i)
    //     for (int j = 0; j < 5; ++j)
    //         b[i][j] = i - j;

    // vector<vector<int>> resClassic = classicMul::matrixMulClassic(a, b, 3, 4, 5);
    // vector<vector<int>> resVinograd = vinogradMul::matrixMulVinograd(a, b, 3, 4, 5);
    // vector<vector<int>> resVinogradWithOpt = vinogradMul::matrixMulVinograd(a, b, 3, 4, 5);

    vector<vector<int>> a = {{1, 2, 1}, {4, 2, 2}, {0, 7, 1}};
    vector<vector<int>> b = {{7, 5, 1}, {2, 1, 2}, {4, 3, 4}};
    vector<vector<int>> c(3, vector<int>(3, 0));

    vector<vector<int>> resClassic = classicMul::matrixMulClassic(a, b, 3, 3, 3);
    strassenMul::matrixMulStrassen(a, b, c, 3);

    c.resize(3);

    // loop to resize the inside of the matrices
    for (int i = 0; i < 3; ++i)
        c[i].resize(3);

    printMatrix(c);
    printMatrix(resClassic);
    // printMatrix(resVinograd);
    // printMatrix(resVinogradWithOpt);

    return 0;
}
