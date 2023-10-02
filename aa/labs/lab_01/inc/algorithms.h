#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <iostream>

#include "matrix.h"

namespace lev
{
int distanceNotRecur(const std::wstring &str1, const std::wstring &str2);

} // namespace lev

namespace damlev
{
int distanceRecur(const std::wstring &str1, const std::wstring &str2);
int distanceRecurWithCaching(const std::wstring &str1, const std::wstring &str2);
int distanceNotRecurWithMatrix(const std::wstring &str1, const std::wstring &str2);
} // namespace damlev

#endif
