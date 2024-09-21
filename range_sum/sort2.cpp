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



void insertionSort(int arr[], int low, int high) {}
void selectionSort(int arr[], int low, int high) {}
void sellSort(int arr[], int low, int high) {}
void quickSort(int arr[], int low, int high) {}
void mergeSort(int arr[], int low, int high) {}
void heapSort(int arr[], int low, int high) {}