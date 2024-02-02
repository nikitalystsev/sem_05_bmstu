#include "conveyor.h"

std::mutex mq1;
std::mutex mq2;

void thrReadFileFunc(const int numAppl, std::queue<conveyorAppl_t> &q1);
void thrProcessFunc(const int numAppl, const int N, std::queue<conveyorAppl_t> &q1, std::queue<conveyorAppl_t> &q2);
void thrLogFunc(const int numAppl, std::queue<conveyorAppl_t> &q2, std::vector<conveyorAppl_t> &vec);

long long int conveyorSolution(const int numAppl, const int numLines, const int strLenght, const int N)
{
    // генерирую файлы с текстами
    for (int i = 0; i < numAppl; ++i)
    {
        std::string inputFilename = "data/text" + std::to_string(i) + ".txt";
        getRandomText(inputFilename, numLines, strLenght);
    }

    std::queue<conveyorAppl_t> q1;
    std::queue<conveyorAppl_t> q2;
    std::vector<conveyorAppl_t> vec;

    std::thread thr1(thrReadFileFunc, numAppl, std::ref(q1));
    std::thread thr2(thrProcessFunc, numAppl, N, std::ref(q1), std::ref(q2));
    std::thread thr3(thrLogFunc, numAppl, std::ref(q2), std::ref(vec));

    thr1.join();
    thr2.join();
    thr3.join();

    long long workTime = printVec(vec, "data/conveyor.txt");

    return workTime;
}

void thrReadFileFunc(const int numAppl, std::queue<conveyorAppl_t> &q1)
{
    for (int i = 0; i < numAppl; ++i)
    {
        conveyorAppl_t appl;

        appl.inputFilename = "data/text" + std::to_string(i) + ".txt";
        appl.outputFilename = "data/outputText" + std::to_string(i) + ".txt";

        clock_gettime(CLOCK_REALTIME, &appl.timeStartRead);
        parallelVersion::readFile(appl.inputFilename, appl.vecTextStr);
        clock_gettime(CLOCK_REALTIME, &appl.timeEndRead);

        mq1.lock();
        q1.push(appl);
        mq1.unlock();
    }
}

void thrProcessFunc(const int numAppl, const int N, std::queue<conveyorAppl_t> &q1, std::queue<conveyorAppl_t> &q2)
{
    for (int i = 0; i < numAppl; ++i)
    {
        while (q1.empty())
            ;

        mq1.lock();
        conveyorAppl_t appl = q1.front();
        q1.pop();
        mq1.unlock();

        clock_gettime(CLOCK_REALTIME, &appl.timeStartProcess);
        parallelVersion::solution(appl.vecTextStr, appl.outputFilename, N, 2);
        clock_gettime(CLOCK_REALTIME, &appl.timeEndProcess);

        mq2.lock();
        q2.push(appl);
        mq2.unlock();
    }
}

void thrLogFunc(const int numAppl, std::queue<conveyorAppl_t> &q2, std::vector<conveyorAppl_t> &vec)
{
    std::ofstream logFile("data/log.txt");

    if (!logFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return;
    }

    for (int i = 0; i < numAppl; ++i)
    {
        while (q2.empty())
            ;

        mq2.lock();
        conveyorAppl_t appl = q2.front();
        q2.pop();
        mq2.unlock();

        clock_gettime(CLOCK_REALTIME, &appl.timeStartLog);
        logFile << appl.inputFilename << ": " << appl.outputFilename << std::endl;
        clock_gettime(CLOCK_REALTIME, &appl.timeEndLog);

        vec.push_back(appl);
    }

    logFile.close();
}

long long int printVec(std::vector<conveyorAppl_t> &vecAppl, std::string filename)
{
    std::ofstream serialLog(filename);

    if (!serialLog.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return -1;
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

    return nanosec;
}