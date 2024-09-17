#include "sorting.h"
#include <ctime>
#include <cstdio>

#define MAX_SIZE    10'000   // 배열의 크기

int arr[MAX_SIZE];
int n = MAX_SIZE;               // 배열의 원소 개수
int maxNumber = 10'001;            // 배열의 원소 중 최대값
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

void testSort(void (*sortingFunc)(int[], int), int arr[], int n) {
    int lo = (n > 20)? n - 20: 0;
    int hi = n - 1;

    initArray(arr, n, maxNumber, seed);
    printArray(arr, lo, hi);

    clock_t start = clock();
    sortingFunc(arr, n);
    int result = (clock() - start) / (CLOCKS_PER_SEC / 1000);
    printf(">> Time: %d ms\n", result);
    printArray(arr, lo, hi);
}

int main()
{
    // printf("\n\n*** [Bubble Sort: Standard]\n");
    // testSort(bubbleSortStandard, arr, n);

    // printf("\n\n*** [Bubble Sort: Iterative]\n");
    // testSort(bubbleSort, arr, n);

    // printf("\n\n*** [Bubble Sort: Recursive]\n");
    // testSort(bubbleSortRecur, arr, n);

    // printf("\n\n*** [Cocktail Shaker Sort]\n");
    // testSort(cocktailSort, arr, n);

    // printf("\n\n*** [Comb Sort]\n");
    // testSort(combSort, arr, n);

    // printf("\n\n*** [Insertion Sort]\n");
    // testSort(insertionSort, arr, n);

    // printf("\n\n*** [Hybrid Sort]\n");
    // testSort(hybridSort, arr, n);

    // printf("\n\n*** [Binary Insertion Sort]\n");
    // testSort(binaryInsertionSort, arr, n);

    // printf("\n\n*** [Shell Sort - Knuth's gap]\n");
    // testSort(shellSortKnuth, arr, n);

    // printf("\n\n*** [Shell Sort]\n");
    // testSort(shellSort, arr, n);

    printf("\n\n*** [Selection Sort]\n");
    testSort(selectionSort, arr, n);



    return 0;
}