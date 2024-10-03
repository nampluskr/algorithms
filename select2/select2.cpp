#include "select2.h"

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }


int bruteForceSelect(int arr[], int low, int high, int k) {
    for (int i = low; i <= high; ++i) {
        int cnt = -1;
        for (int j = low; j <= high; ++j)
            if (arr[j] <= arr[i]) cnt++;
        if (cnt == k) return arr[i];
    }
    return -1;
}

int insertionSelect(int arr[], int low, int high, int k) {
    // Insertion Sort: O(N^2)
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= low && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
    return arr[low + k];
}

/////////////////////////////////////////////////////////////////////
// Quick Select and Its Variations

int lomutoPartition(int arr[], int low, int high) {
    swap(arr[(low + high) / 2], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) 
            swap(arr[++i], arr[j]);

    swap(arr[++i], arr[high]);
    return i;
}

int quickSelectLomutoRecur(int arr[], int low, int high, int k) {
    if (low >= high) return arr[low];

    int pivotIdx = lomutoPartition(arr, low, high);
    if (k < pivotIdx) return quickSelectLomutoRecur(arr, low, pivotIdx - 1, k);
    else if (pivotIdx < k) return quickSelectLomutoRecur(arr, pivotIdx + 1, high, k);
    else return arr[pivotIdx];
}

int quickSelectLomuto(int arr[], int low, int high, int k) {
    return quickSelectLomutoRecur(arr, low, high, low + k);
}

int quickSelectLomutoIter(int arr[], int low, int high, int k) {
    k += low;
    while (low <= high) {
        int pivotIdx = lomutoPartition(arr, low, high);
        if (k < pivotIdx) high = pivotIdx - 1;
        else if (pivotIdx < k) low = pivotIdx + 1;
        else return arr[pivotIdx];
    }
    return arr[low];
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

int quickSelectHoareRecur(int arr[], int low, int high, int k) {
    if (low >= high) return arr[low];

    int pivotIdx = hoarePartition(arr, low, high);
    if (k < pivotIdx) return quickSelectHoareRecur(arr, low, pivotIdx, k);
    else if (pivotIdx < k) return quickSelectHoareRecur(arr, pivotIdx + 1, high, k);
    else return arr[pivotIdx];
}

int quickSelectHoare(int arr[], int low, int high, int k) {
    return quickSelectHoareRecur(arr, low, high, low + k);
}

int quickSelectHoareIter(int arr[], int low, int high, int k) {
    k += low;
    while (low <= high) {
        int pivotIdx = hoarePartition(arr, low, high);
        if (k < pivotIdx) high = pivotIdx;
        else if (pivotIdx < k) low = pivotIdx + 1;
        else return arr[pivotIdx];
    }
    return arr[low];
}

int medianSelect(int arr[], int low, int high) {
    if (low == high) return arr[low];

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int pivotIdx = lomutoPartition(arr, low, high);

        if (mid < pivotIdx) high = pivotIdx - 1;
        else if (pivotIdx < mid) low = pivotIdx + 1;
        else return arr[pivotIdx];
    }
}

/////////////////////////////////////////////////////////////////////
// Heap Select and Its Variations

// i = 0, 1, 2, ... n - 1 [상대적 노드 번호]
void siftDown(int arr[], int low, int high, int i) {
    int cur = low + i;          // smallest index
    int left = low + 2 * i + 1;
    int right = low + 2 * i + 2;

    if (left <= high && arr[left] < arr[cur]) cur = left;
    if (right <= high && arr[right] < arr[cur]) cur = right;
    if (cur != low + i) {
        swap(arr[cur], arr[low + i]);
        siftDown(arr, low, high, cur - low);
    }
}

int heapSelect(int arr[], int low, int high, int k) {
    int n = high - low + 1;
    for (int i = n / 2 - 1; i >= 0; i--)    // heapify
        siftDown(arr, low, high, i);

    // k times heap sort
    for (int i = high; i >= high - k; i--) {
        swap(arr[low], arr[i]);
        siftDown(arr, low, i - 1, 0);       // root: i = 0
    }
    return arr[high - k];
}