#include "algorithms.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale> // Для корректной работы с кириллицей
#include <map>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

int main(void)
{
    std::locale::global(std::locale(""));

    int rc = serialVersion::solution("data/text.txt", "data/output_text.txt", 4);
    rc = parallelVersion::solution("data/text.txt", "data/output_text2.txt", 4, 3);

    return rc;
}
