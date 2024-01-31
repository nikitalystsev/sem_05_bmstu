#include "conveyor.h"
#include "serial.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale> // Для корректной работы с кириллицей
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

int main()
{
    std::locale::global(std::locale(""));

    // serialSolution(10, 100, 100, 4);
    conveyorSolution(10, 100, 100, 4);

    return 0;
}
