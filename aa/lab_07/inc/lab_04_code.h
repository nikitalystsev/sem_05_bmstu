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
int readFile(std::string &filename, std::vector<std::wstring> &vecStrText);

int solution(std::vector<std::wstring> &vecStrText, const std::string &outputFilename, const int ngram, const int numThreads);
} // namespace parallelVersion

void getRandomText(const std::string &filename, const int numStr, const int strLength);

#endif