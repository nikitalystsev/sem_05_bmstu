#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "lab_04_code.h"
#include <algorithm>
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
    timespec timeStartRead;
    timespec timeEndRead;
    timespec timeStartProcess;
    timespec timeEndProcess;
    timespec timeStartLog;
    timespec timeEndLog;
};

#endif