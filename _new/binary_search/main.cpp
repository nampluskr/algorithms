#include "binary_search.h"
#include <cstdio>

void printArray(const int arr[], int low, int high) {
    printf(">> ");
    for (int i = low; i < high; i++)
        printf("%d, ", arr[i]);
    printf("%d\n", arr[high]);
}

int main()
{
    // sorted array
    int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 36;
    printArray(arr, 0, n - 1);
    printf("Search index  = %d\n", binarySearch(arr, n, target));
    printf("Lower index   = %d\n", lowerBound(arr, n, target));
    printf("Upper index   = %d\n", upperBound(arr, n, target));
    printf("Nearest index = %d\n", findNearest(arr, n, target));

    return 0;
}