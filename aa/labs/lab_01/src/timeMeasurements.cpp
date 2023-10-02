#include "timeMeasurements.h"

static std::wstring getRandomWStr(const size_t len)
{
    std::wstring charset = L"0123456789"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz";

    std::wstring result;
    result.resize(len);

    for (size_t i = 0; i < len; ++i)
        result[i] = charset[rand() % charset.length()];

    return result;
}

static unsigned long long getSearchDistTime(
    findDist_t func,
    const std::wstring &str1, const std::wstring &str2)
{
    unsigned long long time;

    time = getMicrosecondsCpuTime();
    func(str1, str2);
    time = getMicrosecondsCpuTime() - time;

    return time;
}

void timeMeasurement(
    size_t lenStr,
    const int nreps,
    std::array<double, 4> &allTime)
{
    std::array<long long int, 4> arrRes = {};

    for (int i = 0; i < nreps; ++i)
    {
        std::wstring str1 = getRandomWStr(lenStr), str2 = getRandomWStr(lenStr);

        arrRes[0] += getSearchDistTime(lev::distanceNotRecur, str1, str2);
        arrRes[1] += getSearchDistTime(damlev::distanceNotRecurWithMatrix, str1, str2);
        arrRes[2] += getSearchDistTime(damlev::distanceRecur, str1, str2);
        arrRes[3] += getSearchDistTime(damlev::distanceRecurWithCaching, str1, str2);
    }

    for (int i = 0; i < 4; ++i)
        allTime[i] = (double)arrRes[i] / nreps;
}

static void printTimeByLenght(const int lenght)
{
    std::array<double, 4> allTime = {};

    timeMeasurement(lenght, N_REPS, allTime);

    wprintf(L"| %6d | %13.3lf | %13.3lf | %15.3lf | %9.3lf |\n",
            lenght, allTime[0], allTime[1], allTime[2], allTime[3]);
}

double printAllTimeMeasurement(const size_t lenghtMax)
{
    std::wcout << GREEN;
    std::wcout << L"------------------------------------------------------------------------\n"
               << L"|                      Замеры времени (наносекунды)                    |\n"
               << L"|----------------------------------------------------------------------|\n"
               << L"| Длина  |               |                                             |\n"
               << L"|(символ)|  Левенштейн   |              Дамерау-Левенштейн             |\n"
               << L"|        | Нерекурсивный | Нерекурсивный |         Рекурсивный         |\n"
               << L"|        |               |               |     Без кэша    |  С кэшэм  |\n"
               << L"------------------------------------------------------------------------\n";

    for (size_t i = 0; i < lenghtMax; ++i)
        printTimeByLenght(i);

    std::wcout << "------------------------------------------------------------------------\n";
    std::wcout << RESET << std::endl;

    return 0;
}