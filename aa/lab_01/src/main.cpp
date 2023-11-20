#include "interface.h"
#include "memoryMeasurements.h"
#include "timeMeasurements.h"

int main()
{

    setlocale(LC_ALL, "ru_RU.UTF-8");

    int menu_item = 0;

    std::wstring word1, word2;

    printMenu();

    while (inputMenuItem(menu_item))
    {
        switch (menu_item)
        {
        case 1:
            inputTwoWStrings(word1, word2);
            printAllDistance(word1, word2);
            break;
        case 2:
            printAllTimeMeasurement(11);
            printAllMemoryMeasurement(11);
            break;
        case 0:
            exit(0);
        default:
            printWrongMenuItem();
            break;
        }

        printMenu();
    }

    // std::wstring str1 = L"", str2 = L"";
    // std::wstring str1 = L"", str2 = L"qwerty";
    // std::wstring str1 = L"doctorwho", str2 = L"";
    // std::wstring str1 = L"code", str2 = L"decoder";
    // std::wstring str1 = L"transposition", str2 = L"transpose";
    // std::wstring str1 = L"asas", str2 = L"saas";
    // std::wstring str1 = L"друзья", str2 = L"рдузия";
    // std::wstring str1 = L"гибралтар", str2 = L"лабрадор";
    // std::wstring str1 = L"АВТОР", str2 = L"АФФТАР";
    // std::wstring str1 = L"moloko", str2 = L"молоко";

    // int dist1 = lev::distanceNotRecur(str1, str2);
    // int dist2 = damlev::distanceRecur(str1, str2);
    // int dist3 = damlev::distanceNotRecurWithMatrix(str1, str2);
    // int dist4 = damlev::distanceRecurWithCaching(str1, str2);

    // std::cout << "dist1 = " << dist1 << std::endl;
    // std::cout << "dist2 = " << dist2 << std::endl;
    // std::cout << "dist3 = " << dist3 << std::endl;
    // std::cout << "dist4 = " << dist4 << std::endl;

    return 0;
}
