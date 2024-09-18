#include "sorting.h"
#include <ctime>
#include <cstdio>

#define MAX_SIZE    100'000          // 배열의 크기

int arr[MAX_SIZE];
int n = MAX_SIZE;                   // 배열의 원소 개수
int maxNumber = 100'000;             // 배열의 원소 중 최대값
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

void test_bubble_sort(int option) {
    if (option == 0) return;

    printf("\n\n*** [Bubble Sort: Iterative]\n");
    testSort(bubbleSortIter, arr, n);

    printf("\n\n*** [Bubble Sort: Recursive]\n");
    testSort(bubbleSortRecur, arr, n);

    printf("\n\n*** [Optimized Bubble Sort]\n");
    testSort(bubbleSortOptimized, arr, n);

    printf("\n\n*** [Cocktail Shaker Sort]\n");
    testSort(cocktailSort, arr, n);

    printf("\n\n*** [Comb Sort]\n");
    testSort(combSort, arr, n);
}

void test_insertion_sort(int option) {
    if (option == 0) return;

    printf("\n\n*** [Insertion Sort]\n");
    testSort(insertionSort, arr, n);

    printf("\n\n*** [Hybrid Sort]\n");
    testSort(hybridSort, arr, n);

    printf("\n\n*** [Binary Insertion Sort]\n");
    testSort(binaryInsertionSort, arr, n);

    printf("\n\n*** [Shell Sort - Knuth's gap]\n");
    testSort(shellSortKnuth, arr, n);

    printf("\n\n*** [Shell Sort]\n");
    testSort(shellSort, arr, n);
}


void test_selection_sort(int option) {
    if (option == 0) return;

    printf("\n\n*** [Selection Sort]\n");
    testSort(selectionSort, arr, n);
}

void test_quick_sort(int option) {
    if (option == 0) return;

    printf("\n\n*** [Quick Sort with Lomuto Partitioning Scheme]\n");
    testSort(lomutoQuickSort, arr, n);

    printf("\n\n*** [Quick Sort with Hoare Partitioning Scheme]\n");
    testSort(hoareQuickSort, arr, n);
}

int sortArray(int arr[], int low, int high) {
    // Insertion sort
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= low && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
    return low + (high - low) / 2;
}

int main()
{
    // test_bubble_sort(0);
    // test_insertion_sort(1);
    // test_selection_sort(0);
    // test_quick_sort(1);

    int arr[] = { 6, 3, 5, 4, 7, 1, 2, 8, 9 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int pivotIdx = choosePivotIndex(arr, 0, n - 1);
    // int pivotIdx = MED3(arr, 0, 3, 5);

    // pivotIdx = findMedianIndex(arr, 0, n - 1);
    pivotIdx = medianOfMedians(arr, 0, n - 1);

    return 0;
}