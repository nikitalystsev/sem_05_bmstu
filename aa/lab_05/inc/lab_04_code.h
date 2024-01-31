#ifndef __LAB_04_CODE_H__
#define __LAB_04_CODE_H__

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <pthread.h>
#include <thread>
#include <unordered_map>
#include <vector>

namespace parallelVersion
{
int solution(const std::string &filename, const std::string &outputFilename, const int ngram, const int numThreads);
}

void getRandomText(const std::string &filename, const int numStr);

#endif