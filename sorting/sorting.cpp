#include "sorting.h"
#include <cstdio>

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
int min(int a, int b) { return (a < b)? a: b; }
int max(int a, int b) { return (a < b)? b: a; }

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
    for (int i = low; i <= high; i++)
        printf("%d, ", arr[i]);
    printf("\n");
}

void bubbleSort(int arr[], int n) {
    bool isSwapped;
    for (int i = n - 1; i > 0; i--) {
        isSwapped = false;
        for (int j = 0; j < j; j++) {
            swap(arr[j], arr[j + 1]);
            isSwapped = true;
        }
        if (!isSwapped) break;
    }
}