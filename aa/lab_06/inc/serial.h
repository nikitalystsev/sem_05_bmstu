#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "lab_04_code.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

// структура заявки (в конвейере такая же будет)
struct serialAppl_t
{
    std::string inputFilename;
    std::string outputFilename;
    int N;
    int numLines;
    int strLenght;
    std::vector<std::wstring> vecTextStr;
    timespec timeStartRead;
    timespec timeEndRead;
    timespec timeStartProcess;
    timespec timeEndProcess;
    timespec timeStartLog;
    timespec timeEndLog;
};

long long int serialSolution(const int numAppl, const int numLines, const int strLenght, const int N);
long long int printVec(std::vector<serialAppl_t> &vecAppl, std::string filename);

#endif