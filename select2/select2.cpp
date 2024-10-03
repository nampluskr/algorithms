#include "select2.h"

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

int lomutoPartition(int arr[], int low, int high) {
    swap(arr[(low + high) / 2], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) 
            swap(arr[++i], arr[j]);
    }
    swap(arr[++i], arr[high]);
    return i;
}

int quickSelectLomuto(int arr[], int low, int high, int k) {
    if (low >= high) return arr[low];

    int pivotIdx = lomutoPartition(arr, low, high);
    if (k < pivotIdx) return quickSelectLomuto(arr, low, pivotIdx - 1, k);
    else if (pivotIdx < k) return quickSelectLomuto(arr, pivotIdx + 1, high, k);
    else return arr[pivotIdx];
}

int quickSelectLomutoIter(int arr[], int low, int high, int k) {
    while (low <= high) {
        int pivotIdx = lomutoPartition(arr, low, high);
        if (k < pivotIdx) high = pivotIdx - 1;
        else if (pivotIdx < k) low = pivotIdx + 1;
        else return arr[pivotIdx];
    }
    return arr[low];
}

void quickSortLomuto(int arr[], int low, int high) {
    if (low >= high) return;

    int pivotIdx = lomutoPartition(arr, low, high);
    quickSortLomuto(arr, low, pivotIdx - 1);
    quickSortLomuto(arr, pivotIdx + 1, high);
}

int hoarePartition(int arr[], int low, int high) {
    int pivot = arr[(low + high) / 2];
    int i = low - 1, j = high + 1;

    while (true) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);

        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    return j;
}

int quickSelectHoare(int arr[], int low, int high, int k) {
    if (low >= high) return arr[low];

    int pivotIdx = hoarePartition(arr, low, high);
    if (k < pivotIdx) return quickSelectHoare(arr, low, pivotIdx, k);
    else if (pivotIdx < k) return quickSelectHoare(arr, pivotIdx + 1, high, k);
    else return arr[pivotIdx];
}

int quickSelectHoareIter(int arr[], int low, int high, int k) {
    while (low <= high) {
        int pivotIdx = hoarePartition(arr, low, high);
        if (k < pivotIdx) high = pivotIdx;
        else if (pivotIdx < k) low = pivotIdx + 1;
        else return arr[pivotIdx];
    }
    return arr[low];
}

void quickSortHoare(int arr[], int low, int high) {
    if (low >= high) return;

    int pivotIdx = hoarePartition(arr, low, high);
    quickSortHoare(arr, low, pivotIdx);
    quickSortHoare(arr, pivotIdx + 1, high);
}

int medianSelect(int arr[], int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int pivotIdx = lomutoPartition(arr, low, high);

        if (mid < pivotIdx) high = pivotIdx - 1;
        else if (pivotIdx < mid) low = pivotIdx + 1;
        else return arr[pivotIdx];
    }
    return arr[low];
}