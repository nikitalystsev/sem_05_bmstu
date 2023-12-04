#include "algorithms.h"
#include <iostream>
#include <vector>

using namespace std;

void printArray(std::vector<int> &A, int size)
{
    for (auto i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
}

// read input array and call mergesort
int main()
{
    srand(100);
    cout << "rand() = " << rand() << endl;
    cout << "rand() = " << rand() << endl;
    // vector<int> myArray = {12, 34, 5, 0, 22, 8, 12, 9};
    // vector<int> tmpMyArray = myArray;

    // cout << "arr.size() = " << myArray.size() << endl;

    // bucketSort::bucketSort(myArray);

    // cout << "bucketSort myArray:\n";
    // printArray(myArray, myArray.size());

    // myArray = tmpMyArray;

    // mergeSort::mergeSort(myArray);

    // cout << "mergeSort myArray:\n";
    // printArray(myArray, myArray.size());

    // myArray = tmpMyArray;

    // radixSort::radixSort(myArray);

    // cout << "radixSort myArray:\n";
    // printArray(myArray, myArray.size());

    return 0;
}
