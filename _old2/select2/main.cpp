#include "select2.h"
#include <cstdio>

void printArray(int arr[], int low, int high) {
    printf(">> ");
    for (int i = low; i < high; i++)
        printf("%d, ", arr[i]);
    printf("%d\n", arr[high]);
}

void testSelect(int (*sortSelect)(int[], int, int, int), int arr[], int low, int high) {
    for (int i = 0; i < high - low + 1; i++) {
        int res = sortSelect(arr, low, high, i);
        printf(">> %2dth element: %d\n", i + 1, res);
    }
}


int main()
{
    int arr[] = { 1, 1, 90, 10, 80, 30, 20, 70, 40, 50, 60, 1, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int value, k = 5;
    int low = 2, high = n - 3;
    printArray(arr, 0, n - 1);

    // testSelect(bruteForceSelect, arr, low, high);
    // testSelect(insertionSelect, arr, low, high);

    // testSelect(quickSelectLomuto, arr, low, high);
    // testSelect(quickSelectLomutoIter, arr, low, high);
    // testSelect(quickSelectHoare, arr, low, high);
    // testSelect(quickSelectHoareIter, arr, low, high);

    // testSelect(heapSelect, arr, low, high);
    testSelect(introSelect, arr, low, high);

    // int res = medianSelect(arr, low, high);
    // printf(">> %d-th element: %d\n", (high - low + 1) / 2 + 1, res);

    printArray(arr, 0, n - 1);
    return 0;
}