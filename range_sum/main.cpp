#include <cstdio>
#include <ctime>
#include "sort2.h"

#define MAX_SIZE    20          // 배열의 크기

int arr[MAX_SIZE];
int n = MAX_SIZE;                // 배열의 원소 개수
int maxNumber = 100;             // 배열의 원소 중 최대값
unsigned long long seed = 42;

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

void initArray(int arr[], int n, int maxNumber, int seed) {
    for (int i = 0; i < n; i++) {
        seed = rand(seed);
        arr[i] = seed % maxNumber;
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
    int low = 0, high = n - 1;
    initArray(arr, n, maxNumber, seed);
    printArray(arr, low, high);
    
    // testSort(bubbleSort, arr, low, high);
    testSort(selectionSort, arr, low, high);
    // testSort(insertionSort, arr, low, high);
    // testSort(shellSort, arr, low, high);

    printArray(arr, low, high);

    return 0;
}