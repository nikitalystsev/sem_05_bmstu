#include "algorithms.h"

static int findMax(vector<int> &arr)
{
    int max = arr[0];

    for (int num : arr)
        if (num > max)
            max = num;

    return max;
}

static int findMin(vector<int> &arr)
{
    int max = arr[0];

    for (int num : arr)
        if (num < max)
            max = num;

    return max;
}

namespace bucketSort
{
void bucketSort(vector<int> &arr)
{
    int n = arr.size();
    int minVal = findMin(arr), maxVal = findMax(arr);
    int bucketRange = (maxVal - minVal) / n + 1;
    int bucketIndex, i, j, index = 0;

    vector<vector<int>> buckets(n);

    for (i = 0; i < n; i++)
    {
        bucketIndex = (arr[i] - minVal) / bucketRange;
        buckets[bucketIndex].push_back(arr[i]);
    }

    for (i = 0; i < n; i++)
        sort(buckets[i].begin(), buckets[i].end());

    for (i = 0; i < n; i++)
        for (j = 0; j < buckets[i].size(); j++)
            arr[index++] = buckets[i][j];
}

} // namespace bucketSort

namespace radixSort
{

static void countSort(vector<int> &arr, int exp)
{
    int n = arr.size();
    int i;

    vector<int> output(n), count(10, 0);

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int> &arr)
{
    int max = findMax(arr);
    int exp;

    for (exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, exp);
}
} // namespace radixSort

namespace mergeSort
{
static void _merge(vector<int> &arr, int low, int high, int mid)
{
    int i, j, k, a;
    int lengthLeft = mid - low + 1;
    int lengthRight = high - mid;

    // Creating two temp arrays to store left and right sub-arrays.
    vector<int> arrLeft(lengthLeft), arrRight(lengthRight);

    // Copying the data from the actual array to left and right temp arrays.
    for (a = 0; a < lengthLeft; a++)
        arrLeft[a] = arr[low + a];

    for (a = 0; a < lengthRight; a++)
        arrRight[a] = arr[mid + 1 + a];

    // Merging the temp arrays back into the actual array.
    i = 0;   // Starting index of arrLeft[].
    j = 0;   // Staring index of arrRight[].
    k = low; // Starting index of merged subarray.

    while (i < lengthLeft && j < lengthRight)
    {
        // Checking and placing the smaller number of both temp arrays into the main array.
        if (arrLeft[i] <= arrRight[j])
        {
            arr[k] = arrLeft[i];
            i++;
        }
        else
        {
            arr[k] = arrRight[j];
            j++;
        }
        k++;
    }

    // After the successful execution of the above loop
    // copying the remaining elements of the left subarray (if remaining).
    while (i < lengthLeft)
    {
        arr[k] = arrLeft[i];
        k++;
        i++;
    }

    // Copying the remaining elements of the right sub array (if remaining).
    while (j < lengthRight)
    {
        arr[k] = arrRight[j];
        k++;
        j++;
    }
}

static void _mergeSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        _mergeSort(arr, low, (low + high) / 2);
        _mergeSort(arr, (low + high) / 2 + 1, high);

        _merge(arr, low, high, (low + high) / 2);
    }
}

void mergeSort(vector<int> &arr)
{
    _mergeSort(arr, 0, arr.size() - 1);
}
} // namespace mergeSort