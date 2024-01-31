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
    // Число, которое вы хотите преобразовать в строку
    int number = 42;

    // Преобразование числа в строку с использованием std::to_string()
    std::string strNumber = std::to_string(number);

    // Вывод результата
    std::cout << "Число как строка: " << strNumber << std::endl;

    return 0;
}
