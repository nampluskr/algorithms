#include "select.h"
#include <cstdio>

void printArray(int arr[], int low, int high) {
    printf(">> ");
    for (int i = low; i < high; i++)
        printf("%d, ", arr[i]);
    printf("%d\n", arr[high]);
}


int main()
{
    int arr[] = { 90, 10, 80, 30, 20, 70, 40, 50, 60 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int value, k = n / 2;

    // printArray(arr, 0, n - 1);
    // // lomutoQuickSort(arr, 0, n - 1);
    // idx = lomutoQuickSelect(arr, 0, n - 1, k);
    // printf(">> %d-th element: %d\n", k + 1, idx);
    // printArray(arr, 0, n - 1);

    // printArray(arr, 0, n - 1);
    // hoareQuickSort(arr, 0, n - 1);
    // // idx = hoareQuickSelect(arr, 0, n - 1, k);
    // // printf(">> %d-th element: %d\n", k + 1, idx);
    // printArray(arr, 0, n - 1);

    // printArray(arr, 0, n - 1);
    // value = lomutoQuickSelectIter(arr, n, k);
    // printf(">> %d-th element: %d\n", k + 1, value);
    // printArray(arr, 0, n - 1);

    printArray(arr, 0, n - 1);
    value = hoareQuickSelectIter(arr, n, k);
    printf(">> %d-th element: %d\n", k + 1, value);
    printArray(arr, 0, n - 1);

    return 0;
}