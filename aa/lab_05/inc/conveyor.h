#ifndef __CONVEYOR_H__
#define __CONVEYOR_H__

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

// структура заявки
struct conveyorAppl_t
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

void conveyorSolution(const int numAppl, const int numLines, const int strLenght, const int N);
void printVec(std::vector<conveyorAppl_t> &vecAppl, std::string filename);

#endif