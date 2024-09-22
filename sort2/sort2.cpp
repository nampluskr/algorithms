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

void selectionSort(int arr[], int low, int high) {
    for (int i = low; i < high; i++) {
        int minIndex = i;
        for (int j = i + 1; j <= high; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        if (minIndex != i) swap(arr[minIndex], arr[i]);
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

void shellSort(int arr[], int low, int high) {
    int gap = 1, n = high - low + 1;
    while (gap < n / 3) gap = gap * 3 + 1;    // 1, 4, 13, 40, 121, 363, 1093, ...

    while (gap >= 1) {
        for (int i = gap; i <= high; i++) {
            int temp = arr[i];
            int j;
            for (j = i - gap; j >= low && arr[j] > temp; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = temp;
        }
        gap /= 3;
    }
}
struct pii { int high, low; };

pii lomutoPartition(int arr[], int low, int high) {
     swap(arr[(low + high) / 2], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[++i], arr[high]);
    return { i - 1, i + 1 };    // default i

}

pii hoarePartition(int arr[], int low, int high) {
    int pivot = arr[(low + high) / 2];  // default
     int i = low - 1, j = high + 1;

    while (true) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);

        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    return { j, j + 1 };    // default j
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pii pivotIndex = lomutoPartition(arr, low, high);
        pii pivotIndex = hoarePartition(arr, low, high);
        quickSort(arr, low, pivotIndex.high);
        quickSort(arr, pivotIndex.low, high);
    }
}

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int arr1[n1], arr2[n2];

    for (int i = 0; i < n1; i++) arr1[i] = arr[low + i];
    for (int j = 0; j < n2; j++) arr2[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) arr[k] = arr1[i++];
        else arr[k] = arr2[j++];
        k++;
    }
    while (i < n1) arr[k++] = arr1[i++];
    while (j < n2) arr[k++] = arr2[j++];
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void heapSort(int arr[], int low, int high) {}

void countingSort(int arr[], int low, int high) {
    int base = 1'000'000;		    // 0 <= arr[j] < base (MAX_NUM)
    int count[base];
    int sorted[high - low + 1];

    for (int j = 0; j < base; j++) count[j] = 0;				        // initialize
    for (int j = low; j <= high; j++) count[arr[j]]++;				    // count
    for (int j = 1; j < base; j++) count[j] += count[j - 1];	        // accumulate
    for (int j = high; j >= low; j--) sorted[--count[arr[j]]] = arr[j]; // sort
    for (int j = low; j <= high; j++) arr[j] = sorted[j - low];         // copy
}

void radixSort10(int arr[], int low, int high) {
    int base = 10;			    // 0 <= arr[j] < base^digits (= 10^6)
    int decimal = 1;
    int count[base];
    int sorted[high - low + 1];

    // counting sort in base 10 for 10^i digit
    for (int i = 0; i < 6; i++, decimal *= 10) {

        for (int j = 0; j < base; j++) count[j] = 0;
        for (int j = low; j <= high; j++) count[arr[j] / decimal % base]++;
        for (int j = 1; j < base; j++) count[j] += count[j - 1];
        for (int j = high; j >= low; j--) sorted[--count[arr[j] / decimal % base]] = arr[j];
        for (int j = low; j <= high; j++) arr[j] = sorted[j - low];
    }
}

void radixSort256(int arr[], int low, int high) {
    int base = (1 << 8);        // 0 <= arr[j] < 2^32 (= 256^4)
    int mask = base - 1;
    int count[base];
    int sorted[high - low + 1];

    // counting sort in base 256 for 256^i digit
    for (int i = 0; i < 32; i += 8) {

        for (int j = 0; j < base; j++) count[j] = 0;
        for (int j = low; j <= high; j++) count[(arr[j] >> i) & mask]++;
        for (int j = 1; j < base; j++) count[j] += count[j - 1];
        for (int j = high; j >= low; j--) sorted[--count[(arr[j] >> i) & mask]] = arr[j];
        for (int j = low; j <= high; j++) arr[j] = sorted[j - low];
    }
}