#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace classicMul
{
vector<vector<int>> matrixMulClassic(
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int cRow, int cCol, int cColRes);
}

namespace vinogradMul
{
vector<vector<int>> matrixMulVinograd(
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int cRow, int cCol, int cColRes);

vector<vector<int>> matrixMulVinogradWithOpt(
    vector<vector<int>> &mtr1,
    vector<vector<int>> &mtr2,
    int cRow, int cCol, int cColRes);
} // namespace vinogradMul

namespace strassenMul
{
void matrixMulStrassen(
    vector<vector<int>> &A,
    vector<vector<int>> &B,
    vector<vector<int>> &C, int d);
}

#endif