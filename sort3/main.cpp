#include "sort.h"
#include <cstdio>

int main()
{
    int arr[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);

    Sorting s;
    s.printArray(arr, 0, n - 1);

    // s.setSortingMethod(new QuickSort(new HoarePartition()));
    // s.setSortingMethod(new QuickSort(new LomutoPartition()));
    // s.setSortingMethod(new MergeSort());
    s.sortArray(arr, 0, n - 1);
    s.printArray(arr, 0, n - 1);


    return 0;
}