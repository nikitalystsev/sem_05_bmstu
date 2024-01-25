#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

namespace serialVersion
{
int solution(const std::string &filename, const std::string &outputFilename, const int ngram);
} // namespace serialVersion

namespace parallelVersion
{
int solution(const std::string &filename, const std::string &outputFilename, const int ngram, const int numThreads);
}

void getRandomText(const std::string &filename, const int numStr);

#endif