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
#include "timeMeasurements.h"

void printMenu(void)
{
    printf("1 - запустить последовательную обработку матриц\n");
    printf("2 - запустить конвейерную обработку матриц\n");
    printf("0 - выход\n\n");
    printf("\n\n\nВыберите пункт меню:\n");
}

int choiceMenuItem(int &menuItem)
{
    if (scanf("%d", &menuItem) == 0)
        return 1;

    if (menuItem < 0 || menuItem > 2)
        return 2;

    return 0;
}

int inputN(void)
{
    puts("Введите число N:");
    int N;

    if (scanf("%d", &N) == 0)
        return 1;

    if (N < 3 || N > 5)
        return 2;

    return N;
}

int inpuNumAppl(void)
{
    puts("Введите количество заявок:");
    int numAppl;

    if (scanf("%d", &numAppl) == 0)
        return 1;

    if (numAppl < 0)
        return 2;

    return numAppl;
}

int inputNumLines(void)
{
    puts("Введите число строк в файле:");
    int numLines;

    if (scanf("%d", &numLines) == 0)
        return 1;

    if (numLines < 0)
        return 2;

    return numLines;
}

int inputStrLenght(void)
{
    puts("Введите длину строки:");
    int strLenght;

    if (scanf("%d", &strLenght) == 0)
        return 1;

    if (strLenght < 0 || strLenght > 200)
        return 2;

    return strLenght;
}

int main()
{
    std::locale::global(std::locale(""));

    int menuItem;
    int rc = 0;
    int N, numLines, strLenght, numAppl;

    while (1)
    {
        srand(time(NULL));

        printMenu();
        if ((rc = choiceMenuItem(menuItem)) != 0)
            goto _exit;

        switch (menuItem)
        {
        case 1:
            N = inputN();
            numAppl = inpuNumAppl();
            numLines = inputNumLines();
            strLenght = inputStrLenght();
            serialSolution(numAppl, numLines, strLenght, N);
            break;
        case 2:
            N = inputN();
            numAppl = inpuNumAppl();
            numLines = inputNumLines();
            strLenght = inputStrLenght();
            conveyorSolution(numAppl, numLines, strLenght, N);
            break;
        case 0:
            exit(0);
            break;
        default:
            break;
        }
    }

_exit:

    return rc;
}
