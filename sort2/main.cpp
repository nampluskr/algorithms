#include <cstdio>
#include <ctime>
#include "sort2.h"

#define MAX_SIZE    15          // 배열의 크기

int arr[MAX_SIZE];
int n = MAX_SIZE;                // 배열의 원소 개수
int maxValue = 100;             // 배열의 원소 중 최대값
unsigned long long seed = 48;

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

void initArray(int arr[], int n, int maxValue, int seed) {
    for (int i = 0; i < n; i++) {
        seed = rand(seed);
        arr[i] = seed % maxValue;
    }
}

void printArray(int arr[], int low, int high) {
    printf(">> ");
    for (int i = low; i < high; i++)
        printf("%d, ", arr[i]);
    printf("%d\n", arr[high]);
}

void testSort(void (*sortFunc)(int[], int, int), int arr[], int low, int high) {
    sortFunc(arr, low, high);
}

int main()
{
    int low = 2, high = n - 3;
    initArray(arr, n, maxValue, seed);
    arr[0] = 99, arr[1] = 98;
    arr[n - 1] = 1, arr[n - 2] = 2;

    printArray(arr, 0, n - 1);

    // testSort(bubbleSort, arr, low, high);       // OK
    // testSort(selectionSort, arr, low, high);    // OK
    // testSort(insertionSort, arr, low, high);    // OK
    // testSort(shellSort, arr, low, high);        // -> low
    // testSort(quickSort, arr, low, high);        // OK
    // testSort(mergeSort, arr, low, high);        // OK
    testSort(countingSort, arr, low, high);
    // testSort(radixSort10, arr, low, high);
    // testSort(radixSort256, arr, low, high);
    printArray(arr, 0, n - 1);

    initArray(arr, n, maxValue, seed);
    arr[0] = 99, arr[1] = 98;
    arr[n - 1] = 1, arr[n - 2] = 2;

    printArray(arr, 0, n - 1);

    return 0;
}