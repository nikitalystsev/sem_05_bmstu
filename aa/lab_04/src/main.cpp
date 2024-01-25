#include "algorithms.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int main()
{
    // Установка локали для корректной работы с символами Юникода
    std::locale::global(std::locale(""));

    int rc = serialVersion::solution("src/text.txt", "output_text.txt", 5);

    return rc;
}
