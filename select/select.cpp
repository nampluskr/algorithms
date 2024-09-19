#include "select.h"

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

int lomutoQuickSelect(int arr[], int low, int high, int k) {
    if (low >= high) return arr[low];

    int pivotIndex = lomutoPartition(arr, low, high);
    if (k < pivotIndex) return lomutoQuickSelect(arr, low, pivotIndex - 1, k);
    else if (pivotIndex < k) return lomutoQuickSelect(arr, pivotIndex + 1, high, k);
    else return arr[pivotIndex];
}

int lomutoQuickSelectIter(int arr[], int n, int k) {
    if (0 <= k && k < n) {
        int low = 0, high = n - 1;
        while (low <= high) {
            int pivotIndex = lomutoPartition(arr, low, high);

            if (k < pivotIndex) high = pivotIndex - 1;
            else if (pivotIndex < k) low = pivotIndex + 1;
            else return arr[pivotIndex];
        }
    }
    return -1;
}

void lomutoQuickSort(int arr[], int low, int high) {
    if (low >= high) return;

    int pivotIndex = lomutoPartition(arr, low, high);
    lomutoQuickSort(arr, low, pivotIndex - 1);
    lomutoQuickSort(arr, pivotIndex + 1, high);
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

int hoareQuickSelect(int arr[], int low, int high, int k) {
    if (low >= high) return arr[low];

    int pivotIndex = hoarePartition(arr, low, high);
    if (k < pivotIndex) return hoareQuickSelect(arr, low, pivotIndex, k);
    else if (pivotIndex < k) return hoareQuickSelect(arr, pivotIndex + 1, high, k);
    else return arr[pivotIndex];
}

int hoareQuickSelectIter(int arr[], int n, int k) {
    if (0 <= k && k < n) {
        int low = 0, high = n - 1;
        while (low <= high) {
            int pivotIndex = hoarePartition(arr, low, high);

            if (k < pivotIndex) high = pivotIndex;
            else if (pivotIndex < k) low = pivotIndex + 1;
            else return arr[pivotIndex];
        }
    }
    return -1;
}

void hoareQuickSort(int arr[], int low, int high) {
    if (low >= high) return;

    int pivotIndex = hoarePartition(arr, low, high);
    hoareQuickSort(arr, low, pivotIndex);
    hoareQuickSort(arr, pivotIndex + 1, high);
}

int medianSelect(int arr[], int low, int high) {
    if (low == high) return arr[low];

    int mid = low + (high - low) / 2;
    while (low <= high) {
        int pivotIndex = lomutoPartition(arr, low, high);

        if (mid < pivotIndex) high = pivotIndex - 1;
        else if (pivotIndex < mid) low = pivotIndex + 1;
        else return arr[pivotIndex];
    }
    return -1;
}