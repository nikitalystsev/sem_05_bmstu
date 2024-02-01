#include "serial.h"

void serialSolution(const int numAppl, const int numLines, const int strLenght, const int N)
{
    // генерирую файлы с текстами
    for (int i = 0; i < numAppl; ++i)
    {
        std::string inputFilename = "data/text" + std::to_string(i) + ".txt";
        getRandomText(inputFilename, numLines, strLenght);
    }

    std::ofstream logFile("data/log.txt");

    if (!logFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return;
    }

    std::vector<serialAppl_t> vecAppl;

    for (int i = 0; i < numAppl; ++i)
    {
        serialAppl_t appl;

        appl.inputFilename = "data/text" + std::to_string(i) + ".txt";
        appl.outputFilename = "data/outputText" + std::to_string(i) + ".txt";
        appl.N = N;
        appl.numLines = numLines;
        appl.strLenght = strLenght;

        std::vector<std::wstring> vecTextStr;

        clock_gettime(CLOCK_REALTIME, &appl.timeStartRead);
        parallelVersion::readFile(appl.inputFilename, vecTextStr);
        clock_gettime(CLOCK_REALTIME, &appl.timeEndRead);

        clock_gettime(CLOCK_REALTIME, &appl.timeStartProcess);
        parallelVersion::solution(vecTextStr, appl.outputFilename, N, 2);
        clock_gettime(CLOCK_REALTIME, &appl.timeEndProcess);

        clock_gettime(CLOCK_REALTIME, &appl.timeStartLog);
        logFile << appl.inputFilename << ": " << appl.outputFilename << std::endl;
        clock_gettime(CLOCK_REALTIME, &appl.timeEndLog);

        vecAppl.push_back(appl);
    }

    logFile.close();

    printVec(vecAppl, "data/serial.txt");
}

void printVec(std::vector<serialAppl_t> &vecAppl, std::string filename)
{
    std::ofstream serialLog(filename);

    if (!serialLog.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return;
    }

    timespec min = vecAppl[0].timeStartRead;

    for (size_t i = 0; i < vecAppl.size(); ++i)
        if (min.tv_sec > vecAppl[i].timeStartRead.tv_sec || (min.tv_sec == vecAppl[i].timeStartRead.tv_sec && min.tv_nsec > vecAppl[i].timeStartRead.tv_nsec))
            min = vecAppl[i].timeStartRead;

    long long nanosec;
    long long min_nano = min.tv_sec * 1000000000 + min.tv_nsec;

    for (int i = 0; i < (int)vecAppl.size(); ++i)
    {
        nanosec = vecAppl[i].timeStartRead.tv_sec * 1000000000 + vecAppl[i].timeStartRead.tv_nsec;
        nanosec -= min_nano;
        serialLog << "Заявка " << i << ": start read    " << nanosec << " ns" << std::endl;
        nanosec = vecAppl[i].timeEndRead.tv_sec * 1000000000 + vecAppl[i].timeEndRead.tv_nsec;
        nanosec -= min_nano;
        serialLog << "Заявка " << i << ": end read      " << nanosec << " ns" << std::endl;

        nanosec = vecAppl[i].timeStartProcess.tv_sec * 1000000000 + vecAppl[i].timeStartProcess.tv_nsec;
        nanosec -= min_nano;
        serialLog << "Заявка " << i << ": start process " << nanosec << " ns" << std::endl;
        nanosec = vecAppl[i].timeEndProcess.tv_sec * 1000000000 + vecAppl[i].timeEndProcess.tv_nsec;
        nanosec -= min_nano;
        serialLog << "Заявка " << i << ": end process   " << nanosec << " ns" << std::endl;

        nanosec = vecAppl[i].timeStartLog.tv_sec * 1000000000 + vecAppl[i].timeStartLog.tv_nsec;
        nanosec -= min_nano;
        serialLog << "Заявка " << i << ": start log     " << nanosec << " ns" << std::endl;
        nanosec = vecAppl[i].timeEndLog.tv_sec * 1000000000 + vecAppl[i].timeEndLog.tv_nsec;
        nanosec -= min_nano;
        serialLog << "Заявка " << i << ": end log       " << nanosec << " ns" << std::endl;
    }
}
