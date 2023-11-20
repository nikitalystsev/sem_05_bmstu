#include "algorithms.h"

namespace lev
{
static int distanceNotRecurWithMatrix(const std::wstring &str1, const std::wstring &str2)
{
    size_t l1 = str1.length();
    size_t l2 = str2.length();

    int **mtr = matrix_alloc(l1 + 1, l2 + 1);

    for (size_t i = 0; i <= l1; ++i)
        mtr[i][0] = i;

    for (size_t j = 0; j <= l2; ++j)
        mtr[0][j] = j;

    for (size_t i = 1; i <= l1; ++i)
        for (size_t j = 1; j <= l2; ++j)
        {
            int isEqual = str1[i - 1] == str2[j - 1] ? 0 : 1;
            mtr[i][j] = std::min({mtr[i][j - 1] + 1, mtr[i - 1][j] + 1, mtr[i - 1][j - 1] + isEqual});
        }

    int res = mtr[l1][l2];
    matrix_free(mtr, l1 + 1);

    return res;
}

static void swapArrays(int arr1[], int arr2[], const int size)
{
    for (int i = 0; i < size; ++i)
        std::swap(arr1[i], arr2[i]);
}

static void printArray(const int arr[], const int size)
{
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";

    std::cout << std::endl;
}

int distanceNotRecur(const std::wstring &str1, const std::wstring &str2)
{
    size_t l1 = str1.length(), l2 = str2.length();

    int currRow[l2 + 1] = {}, prevRow[l2 + 1] = {};

    for (size_t i = 0; i <= l2; ++i)
        prevRow[i] = i;

    for (size_t i = 1; i <= l1; ++i)
    {
        currRow[0] = i;

        for (size_t j = 1; j <= l2; ++j)
        {
            int isEqual = str1[i - 1] == str2[j - 1] ? 0 : 1;
            currRow[j] = std::min({currRow[j - 1] + 1, prevRow[j] + 1, prevRow[j - 1] + isEqual});
        }

        swapArrays(prevRow, currRow, l2 + 1);
    }

    return prevRow[l2];
}
} // namespace lev

namespace damlev
{
static int _distanceRecur(const std::wstring &str1, const std::wstring &str2, const size_t i, const size_t j)
{
    if (std::min(i, j) == 0)
        return std::max(i, j);

    int isEqual = str1[i - 1] == str2[j - 1] ? 0 : 1;

    int tmp_res = std::min({_distanceRecur(str1, str2, i, j - 1) + 1,
                            _distanceRecur(str1, str2, i - 1, j) + 1,
                            _distanceRecur(str1, str2, i - 1, j - 1) + isEqual});
    if (i > 1 && j > 1 &&
        str1[i - 1] == str2[j - 2] &&
        str1[i - 2] == str2[j - 1])
        tmp_res = std::min(tmp_res, _distanceRecur(str1, str2, i - 2, j - 2) + 1);

    return tmp_res;
}

int distanceRecur(const std::wstring &str1, const std::wstring &str2)
{
    size_t l1 = str1.length(), l2 = str2.length();

    return _distanceRecur(str1, str2, l1, l2);
}

static int _distanceRecurWithCaching(const std::wstring &str1, const std::wstring &str2, const size_t i, const size_t j, int **cache)
{
    if (cache[i][j] != -1)
        return cache[i][j];

    if (std::min(i, j) == 0)
        return std::max(i, j);

    int isEqual = str1[i - 1] == str2[j - 1] ? 0 : 1;

    cache[i][j] = std::min({_distanceRecurWithCaching(str1, str2, i, j - 1, cache) + 1,
                            _distanceRecurWithCaching(str1, str2, i - 1, j, cache) + 1,
                            _distanceRecurWithCaching(str1, str2, i - 1, j - 1, cache) + isEqual});
    if (i > 1 && j > 1 &&
        str1[i - 1] == str2[j - 2] &&
        str1[i - 2] == str2[j - 1])
        cache[i][j] = std::min(cache[i][j], _distanceRecurWithCaching(str1, str2, i - 2, j - 2, cache) + 1);

    return cache[i][j];
}

int distanceRecurWithCaching(const std::wstring &str1, const std::wstring &str2)
{
    size_t l1 = str1.length(), l2 = str2.length();
    int **cache = matrix_alloc(l1 + 1, l2 + 1, -1);

    int res = _distanceRecurWithCaching(str1, str2, l1, l2, cache);
    matrix_free(cache, l1 + 1);

    return res;
}

int distanceNotRecurWithMatrix(const std::wstring &str1, const std::wstring &str2)
{
    size_t l1 = str1.length(), l2 = str2.length();

    int **mtr = matrix_alloc(l1 + 1, l2 + 1);

    for (size_t i = 0; i <= l1; ++i)
        mtr[i][0] = i;

    for (size_t j = 0; j <= l2; ++j)
        mtr[0][j] = j;

    for (size_t i = 1; i <= l1; ++i)
        for (size_t j = 1; j <= l2; ++j)
        {
            int isEqual = str1[i - 1] == str2[j - 1] ? 0 : 1;

            mtr[i][j] = std::min({mtr[i][j - 1] + 1,
                                  mtr[i - 1][j] + 1,
                                  mtr[i - 1][j - 1] + isEqual});

            if (i > 1 && j > 1 &&
                str1[i - 1] == str2[j - 2] &&
                str1[i - 2] == str2[j - 1])
                mtr[i][j] = std::min(mtr[i][j], mtr[i - 2][j - 2] + 1);
        }

    int res = mtr[l1][l2];
    matrix_free(mtr, l1 + 1);

    return res;
}
} // namespace damlev