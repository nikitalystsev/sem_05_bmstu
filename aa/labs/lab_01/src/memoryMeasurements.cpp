#include "memoryMeasurements.h"

int calcMemoryLev(const size_t lenght)
{
    int resMemory = 0;

    resMemory += (2 * (lenght + 1) * sizeof(int)); // два массива
    resMemory += (2 * sizeof(std::wstring));       // сам объект строки
    resMemory += (2 * sizeof(wchar_t) * lenght);   // сами строки
    resMemory += (2 * sizeof(size_t));             // длины строк
    resMemory += sizeof(int);                      // isEqual

    return resMemory;
}

int calcMemoryDamLevRec(const size_t lenght)
{
    int resMemory = 0;

    resMemory += (lenght + lenght);                        // сумма длин входящих строк
    resMemory *= (2 * sizeof(size_t) + (2 * sizeof(int))); // tmp_res и isEqual и длины строк
    resMemory += (2 * sizeof(std::wstring));               // сам объект строки
    resMemory += (2 * sizeof(wchar_t) * lenght);           // сами строки

    return resMemory;
}

int calcMemoryDamLevRecCache(const size_t lenght)
{
    int resMemory = 0;

    resMemory += (lenght + lenght);                           // сумма длин входящих строк
    resMemory *= (2 * sizeof(size_t) + sizeof(int));          // isEqual и длины строк
    resMemory += (sizeof(int) * (lenght + 1) * (lenght + 1)); // сама матрица
    resMemory += sizeof(int **);                              // указатель на матрицу
    resMemory += (lenght + 1) * sizeof(int *);                // lenght + 1 указателей на строки матрицы
    resMemory += sizeof(int);                                 // переменная res
    resMemory += (2 * sizeof(std::wstring));                  // сам объект строки
    resMemory += (2 * sizeof(wchar_t) * lenght);              // сами строки

    return resMemory;
}

int calcMemoryDamLevNotRec(const size_t lenght)
{
    int resMemory = 0;

    resMemory += (sizeof(int) * (lenght + 1) * (lenght + 1)); // сама матрица
    resMemory += sizeof(int **);                              // указатель на матрицу
    resMemory += (lenght + 1) * sizeof(int *);                // lenght + 1 указателей на строки матрицы
    resMemory += (2 * sizeof(std::wstring));                  // сами объекты строк
    resMemory += (2 * sizeof(wchar_t) * lenght);              // сами строки
    resMemory += (2 * sizeof(size_t));                        // длины строк
    resMemory += (2 * sizeof(int));                           // isEqual и res

    return resMemory;
}

static void printMemoryByLenght(const int lenght)
{
    wprintf(L"| %6d | %13d | %13d | %8d | %9d |\n", lenght, calcMemoryLev(lenght),
            calcMemoryDamLevNotRec(lenght), calcMemoryDamLevRec(lenght), calcMemoryDamLevRecCache(lenght));
}

double printAllMemoryMeasurement(const size_t lenghtMax)
{
    std::wcout << GREEN;
    std::wcout << L"-----------------------------------------------------------------\n"
               << L"|                      Замеры памяти (байты)                    |\n"
               << L"|---------------------------------------------------------------|\n"
               << L"| Длина  |               |                                      |\n"
               << L"|(символ)|  Левенштейн   |          Дамерау-Левенштейн          |\n"
               << L"|        | Нерекурсивный | Нерекурсивный |     Рекурсивный      |\n"
               << L"|        |               |               | Без кэша |  С кэшом  |\n"
               << L"-----------------------------------------------------------------\n";

    for (size_t i = 0; i < lenghtMax; ++i)
        printMemoryByLenght(i);

    std::wcout << "-----------------------------------------------------------------\n";
    std::wcout << RESET << std::endl;

    return 0;
}
