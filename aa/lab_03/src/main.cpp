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

    vector<int> myarray = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    mergeSort::mergeSort(myarray);

    cout << "Sorted array\n";
    for (int i = 0; i < 10; i++)
    {
        cout << myarray[i] << "\t";
    }
}
