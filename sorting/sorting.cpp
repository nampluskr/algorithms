#include "sorting.h"
#include <cstdio>



/////////////////////////////////////////////////////////////////////
void bubbleSortIter(int arr[], int n) {
    for (int i = n - 1; i > 0 ; i--)
        for (int j = 0; j < i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);

//     for (int i = 0; i < n - 1; i++)
//         for (int j = 0; j < n - i - 1; j++)
//             if (arr[j] > arr[j + 1])
//                 swap(arr[j], arr[j + 1]);
}

void bubbleSortRecur(int arr[], int n) {
    if (n == 1) return;     // base case
     for (int j = 0; j < n - 1; j++)
        if (arr[j] > arr[j + 1])
            swap(arr[j], arr[j + 1]);
     bubbleSortRecur(arr, n - 1);
}

void bubbleSortOptimized(int arr[], int n) {
    bool isSwapped;
    for (int i = n - 1; i > 0 ; i--) {
        isSwapped = false;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
        }
        if (!isSwapped) break;
    }
}

void cocktailSort(int arr[], int n) {
    bool isSwapped = true;
    int lo = 0, hi = n - 1;

    while (isSwapped) {
        isSwapped = false;
        for (int i = lo; i < hi; i++)
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        if (!isSwapped) break;

        isSwapped = false;
        hi--;
        for (int i = hi - 1; i >= lo; i--)
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        lo++;
    }
}

void combSort(int arr[], int n) {
    bool isSwapped = true;
    int gap = n;
    double shrinkFactor = 1.3;

    while (isSwapped || gap > 1) {
        isSwapped = false;
        gap = max(1, (int)(gap / shrinkFactor));

        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                isSwapped = true;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 작은 데이터에 대해서는 버블 정렬의 간단함, 거의 정렬된 데이터에 대해서는 삽입 정렬의 효율성을 활용
// gap 값을 조절하여 다양한 데이터에 대해 최적의 성능 가능
void hybridSort(int arr[], int n) {
    int gap = 10;
    bool isSwapped;
    for (int i = 1; i < n; i += gap) {
        isSwapped = false;
        for (int j = i; j < min(i + gap, n); ++j) {
            for (int k = j; k > i && arr[k - 1] > arr[k]; --k) {
                swap(arr[k - 1], arr[k]);
                isSwapped = true;
            }
        }
        if (!isSwapped) break;
    }
     insertionSort(arr, n);
}

void binaryInsertionSort(int arr[], int n) {
    int i, key, j, left, right, mid;
    for (i = 1; i < n; i++) {
        key = arr[i];
        left = 0;
        right = i - 1;

        while (left <= right) {
            mid = (left + right) / 2;
            if (arr[mid] < key) left = mid + 1;
            else right = mid - 1;
        }
        for (j = i - 1; j >= left; j--)
            arr[j + 1] = arr[j];

        arr[left] = key;
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void shellSortKnuth(int arr[], int n) {
    int gap = 1;
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

/////////////////////////////////////////////////////////////////////
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        if (minIndex != i) swap(arr[minIndex], arr[i]);
    }
}


