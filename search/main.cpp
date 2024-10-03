#include "search.h"
#include <cstdio>

#define MAX_SIZE    15          // 배열의 크기

int arr[MAX_SIZE];
int n = MAX_SIZE;                // 배열의 원소 개수
int maxValue = 10000;             // 배열의 원소 중 최대값
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

void testSearch(int (*searchFunc)(int[], int, int, int), int arr[], int low, int high) {
    int res, target;

    target = 10;
    res = searchFunc(arr, low, high, target);
    printf(">> target=%4d, index=%4d\n", target, res);

    target = 353;
    res = searchFunc(arr, low, high, target);
    printf(">> target=%4d, index=%4d\n", target, res);

    target = 6461;
    res = searchFunc(arr, low, high, target);
    printf(">> target=%4d, index=%4d\n", target, res);
}


int main()
{
    int low = 2, high = n - 3;
    initArray(arr, n, maxValue, seed);
    arr[0] = 99, arr[1] = 98;
    arr[n - 1] = 1, arr[n - 2] = 2;

    // printArray(arr, 0, n - 1);
    // testSearch(linearSearch, arr, low, high);
    // testSearch(linearSearchRecur, arr, low, high);
    // testSearch(sentinelSearch, arr, low, high);
    // testSearch(tranpositionSearch, arr, low, high);
    // testSearch(searchMoveToFront, arr, low, high);

    insertionSort(arr, low, high);
    printArray(arr, 0, n - 1);
    // testSearch(binarySearch, arr, low, high);
    // testSearch(binarySearchRecur, arr, low, high);
    // testSearch(lowerBound, arr, low, high);
    // testSearch(lowerBoundRecur, arr, low, high);
    // testSearch(upperBound, arr, low, high);
    // testSearch(upperBoundRecur, arr, low, high);


    return 0;
}