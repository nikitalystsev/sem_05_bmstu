#include "algorithms.h"

namespace classicMul
{
vector<vector<int>> matrixMulClassic(
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int cRow, int cCol, int cColRes)
{ // N M P

    vector<vector<int>> mtrRes(cRow, vector<int>(cColRes, 0));

    for (int i = 0; i < cRow; ++i)
        for (int j = 0; j < cColRes; ++j)
            for (int k = 0; k < cCol; ++k)
                mtrRes[i][j] = mtrRes[i][j] + mtr1[i][k] * mtr2[k][j];

    return mtrRes;
}
} // namespace classicMul

namespace vinogradMul
{
vector<vector<int>> matrixMulVinograd(
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int cRow, int cCol, int cColRes)
{ // N M P
    vector<vector<int>> mtrRes(cRow, vector<int>(cColRes, 0));

    // int rowFactor[cRow], colFactor[cColRes];

    vector<int> rowFactor(cRow, 0), colFactor(cRow, 0);

    for (int i = 0; i < cRow; ++i)
        for (int j = 0; j < cCol / 2; ++j)
            rowFactor[i] = rowFactor[i] + mtr1[i][2 * j] * mtr1[i][2 * j + 1];

    for (int j = 0; j < cColRes; ++j)
        for (int i = 0; i < cCol / 2; ++i)
            colFactor[j] = colFactor[j] + mtr2[i * 2][j] * mtr2[i * 2 + 1][j];

    for (int i = 0; i < cRow; ++i)
        for (int j = 0; j < cColRes; ++j)
        {
            mtrRes[i][j] = -rowFactor[i] - colFactor[j];

            for (int k = 0; k < cCol / 2; ++k)
                mtrRes[i][j] = mtrRes[i][j] + (mtr1[i][2 * k] + mtr2[2 * k + 1][j]) * (mtr1[i][2 * k + 1] + mtr2[2 * k][j]);
        }

    if (cCol % 2 != 0)
        for (int i = 0; i < cCol; ++i)
            for (int j = 0; j < cColRes; ++j)
                mtrRes[i][j] = mtrRes[i][j] + mtr1[i][cCol - 1] * mtr2[cCol - 1][j];

    return mtrRes;
}

vector<vector<int>> matrixMulVinogradWithOpt(
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int cRow, int cCol, int cColRes)
{ // N M P
    vector<vector<int>> mtrRes(cRow, vector<int>(cColRes, 0));

    // int rowFactor[cRow], colFactor[cColRes];

    vector<int> rowFactor(cRow, 0), colFactor(cRow, 0);

    int cCol_half = cCol / 2;

    for (int i = 0; i < cRow; ++i)
        for (int j = 0; j < cCol_half; ++j)
            rowFactor[i] += mtr1[i][j << 1] * mtr1[i][(j << 1) + 1];

    for (int j = 0; j < cColRes; ++j)
        for (int i = 0; i < cCol_half; ++i)
            colFactor[j] += mtr2[i << 1][j] * mtr2[(i << 1) + 1][j];

    for (int i = 0; i < cRow; ++i)
        for (int j = 0; j < cColRes; ++j)
        {
            mtrRes[i][j] = -rowFactor[i] - colFactor[j];

            for (int k = 0; k < cCol_half; ++k)
                mtrRes[i][j] += (mtr1[i][k << 1] + mtr2[(k << 1) + 1][j]) * (mtr1[i][(k << 1) + 1] + mtr2[k << 1][j]);
        }

    if (cCol % 2 != 0)
        for (int i = 0; i < cCol; ++i)
            for (int j = 0; j < cColRes; ++j)
                mtrRes[i][j] += mtr1[i][cCol - 1] * mtr2[cCol - 1][j];

    return mtrRes;
}
} // namespace vinogradMul

namespace strassenMul
{
void split(vector<vector<int>> &A, vector<vector<int>> &B,
           int row, int col, int d)
{
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++)
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++)
            B[i1][j1] = A[i2][j2];
}

void join(vector<vector<int>> &A, vector<vector<int>> &B,
          int row, int col, int d)
{
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++)
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++)
            B[i2][j2] = A[i1][j1];
}

void add(vector<vector<int>> &A,
         vector<vector<int>> &B,
         vector<vector<int>> &C, int d)
{
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(vector<vector<int>> &A,
         vector<vector<int>> &B,
         vector<vector<int>> &C, int d)
{
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void matrixMulStrassen(vector<vector<int>> &A,
                       vector<vector<int>> &B,
                       vector<vector<int>> &C, int d)
{
    if (!(d && !(d & (d - 1)))) // если d не степень двойки
    {
        d = pow(2, ceil(log2(d)));
        A.resize(d), B.resize(d), C.resize(d);

        for (int i = 0; i < d; ++i)
            A[i].resize(d), B[i].resize(d), C[i].resize(d);
    }

    if (d <= 86)
    {
        C = classicMul::matrixMulClassic(A, B, d, d, d);
        return;
    }

    int new_d = d / 2;

    vector<int> inside(new_d);

    vector<vector<int>> A11(new_d, inside);
    vector<vector<int>> A12(new_d, inside);
    vector<vector<int>> A21(new_d, inside);
    vector<vector<int>> A22(new_d, inside);
    vector<vector<int>> B11(new_d, inside);
    vector<vector<int>> B12(new_d, inside);
    vector<vector<int>> B21(new_d, inside);
    vector<vector<int>> B22(new_d, inside);
    vector<vector<int>> C11(new_d, inside);
    vector<vector<int>> C12(new_d, inside);
    vector<vector<int>> C21(new_d, inside);
    vector<vector<int>> C22(new_d, inside);

    split(A, A11, 0, 0, new_d);
    split(A, A12, 0, new_d, new_d);
    split(A, A21, new_d, 0, new_d);
    split(A, A22, new_d, new_d, new_d);
    split(B, B11, 0, 0, new_d);
    split(B, B12, 0, new_d, new_d);
    split(B, B21, new_d, 0, new_d);
    split(B, B22, new_d, new_d, new_d);

    vector<vector<int>> result1(new_d, inside);
    vector<vector<int>> result2(new_d, inside);

    add(A11, A22, result1, new_d);
    add(B11, B22, result2, new_d);
    vector<vector<int>> M1(new_d, inside);
    matrixMulStrassen(result1, result2, M1, new_d);

    add(A21, A22, result1, new_d);
    vector<vector<int>> M2(new_d, inside);
    matrixMulStrassen(result1, B11, M2, new_d);

    sub(B12, B22, result2, new_d);
    vector<vector<int>> M3(new_d, inside);
    matrixMulStrassen(A11, result2, M3, new_d);

    sub(B21, B11, result2, new_d);
    vector<vector<int>> M4(new_d, inside);
    matrixMulStrassen(A22, result2, M4, new_d);

    add(A11, A12, result1, new_d);
    vector<vector<int>> M5(new_d, inside);
    matrixMulStrassen(result1, B22, M5, new_d);

    sub(A21, A11, result1, new_d);
    add(B11, B12, result2, new_d);
    vector<vector<int>> M6(new_d, inside);
    matrixMulStrassen(result1, result2, M6, new_d);

    sub(A12, A22, result1, new_d);
    add(B21, B22, result2, new_d);
    vector<vector<int>> M7(new_d, inside);
    matrixMulStrassen(result1, result2, M7, new_d);

    add(M1, M4, result1, new_d);
    add(result1, M7, result2, new_d);
    sub(result2, M5, C11, new_d);

    add(M3, M5, C12, new_d);

    add(M2, M4, C21, new_d);

    sub(M1, M2, result1, new_d);
    add(M3, M6, result2, new_d);
    add(result1, result2, C22, new_d);

    join(C11, C, 0, 0, new_d);
    join(C12, C, 0, new_d, new_d);
    join(C21, C, new_d, 0, new_d);
    join(C22, C, new_d, new_d, new_d);
}

} // namespace strassenMul
