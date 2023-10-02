#include "interface.h"

void printMenu()
{
    std::wcout << TURQ;
    std::wcout << L"1. Вычислить расстояния Левенштейна и Дамерау-Левенштейна; \n"
                  "  - 1) Нерекурсивный Левенштейн; \n"
                  "  - 2) Нерекурсивный Дамерау-Левенштейн; \n"
                  "  - 3) Рекурсивный Дамерау-Левенштейн; \n"
                  "  - 4) Рекурсивный Дамерау-Левенштейн с кэшированием.\n"
                  "2. Замерить время и память реализаций Левенштейна "
                  "и Дамерау-Левенштейна.\n"
                  "0. Выход из программы\n"
               << std::endl;
    std::wcout << RESET;
}

int inputMenuItem(int &menuItem)
{
    std::wcout << L"Выберите пункт меню: ";

    if (!(std::wcin >> menuItem))
        return 0;

    return 1;
}

void inputTwoWStrings(std::wstring &str1, std::wstring &str2)
{
    // Ввод первой строки
    std::wcout << L"Введите первую строку: ";
    std::wcin >> str1;

    // Ввод второй строки
    std::wcout << L"Введите вторую строку: ";
    std::wcin >> str2;
}

void printAllDistance(const std::wstring &word1, const std::wstring &word2)
{
    int result = 0;

    std::wcout << GREEN << std::endl;
    result = lev::distanceNotRecur(word1, word2);
    std::wcout << L"Нерекурсивный Левенштейн:                      "
               << result << std::endl;
    result = damlev::distanceNotRecurWithMatrix(word1, word2);
    std::wcout << L"Нерекурсивный Дамерау-Левенштейн:              "
               << result << std::endl;
    result = damlev::distanceRecur(word1, word2);
    std::wcout << L"Рекурсивный Дамерау-Левенштейн:                "
               << result << std::endl;
    result = damlev::distanceRecurWithCaching(word1, word2);
    std::wcout << L"Рекурсивный Дамерау-Левенштейн с кэшированием: "
               << result << std::endl;
    std::wcout << RESET << std::endl;
}

void printWrongMenuItem()
{
    std::wcout << RED;
    std::wcout << L"Некорректный номер пункта меню, попробуйте еще раз.\n"
               << std::endl;
    std::wcout << RESET;
}