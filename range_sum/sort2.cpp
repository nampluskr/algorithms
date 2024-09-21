#include "sort2.h"

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
inline int min(int a, int b) { return (a < b)? a: b; }
inline int max(int a, int b) { return (a < b)? b: a; }

void bubbleSort(int arr[], int low, int high) {
    bool isSwapped;
    for (int i = high; i > low ; i--) {
        isSwapped = false;
        for (int j = low; j < i; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
        }
        if (!isSwapped) break;
    }
}

void insertionSort(int arr[], int low, int high) {
        for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= low && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int low, int high) {
    for (int i = low; i < high; i++) {
        int minIndex = i;
        for (int j = i + 1; j <= high; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        if (minIndex != i) swap(arr[minIndex], arr[i]);
    }
}

void shellSort(int arr[], int low, int high) {
    int gap = 1, n = high - low + 1;
    while (gap < n / 3) gap = gap * 3 + 1;    // 1, 4, 13, 40, 121, 363, 1093, ...

    while (gap >= 1) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = temp;
        }
        gap /= 3;
    }
}

void quickSort(int arr[], int low, int high) {}
void mergeSort(int arr[], int low, int high) {}
void heapSort(int arr[], int low, int high) {}