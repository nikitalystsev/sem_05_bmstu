#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace bucketSort
{
void bucketSort(vector<int> &arr);
}

namespace radixSort
{
void radixSort(vector<int> &arr);
}

namespace mergeSort
{
void mergeSort(vector<int> &arr);
}

#endif