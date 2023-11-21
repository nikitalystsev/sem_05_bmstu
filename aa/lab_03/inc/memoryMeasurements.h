#ifndef __MEMORY_MEASUREMENTS_H__
#define __MEMORY_MEASUREMENTS_H__

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

int calcBucketSortMem(const int size);
int calcRadixSortMem(const int size);
int calcMergeSortMem(const int size);

#endif