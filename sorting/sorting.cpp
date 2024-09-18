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
    int low = 0, high = n - 1;

    while (isSwapped) {
        isSwapped = false;
        for (int i = low; i < high; i++)
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        if (!isSwapped) break;

        isSwapped = false;
        high--;
        for (int i = high - 1; i >= low; i--)
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        low++;
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
        int j;
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
}

// 작은 데이터에 대해서는 버블 정렬의 간단함 활용
// 거의 정렬된 데이터에 대해서는 삽입 정렬의 효율성을 활용
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
    int i, key, j, low, hight, mid;
    for (i = 1; i < n; i++) {
        key = arr[i];
        low = 0;
        hight = i - 1;

        while (low <= hight) {
            mid = (low + hight) / 2;
            if (arr[mid] < key) low = mid + 1;
            else hight = mid - 1;
        }
        for (j = i - 1; j >= low; j--)
            arr[j + 1] = arr[j];

        arr[low] = key;
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


/////////////////////////////////////////////////////////////////////
int lomutoPartition(int arr[], int low, int high) {
    int pivotIndex = MED3(arr, low, (low + high) / 2, high);
    swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[++i], arr[high]);  // 피벗을 최종 위치로 이동
    return i;

}

int hoarePartition(int arr[], int low, int high) {
    // int pivot = arr[(low + high) / 2];  // default
    int pivotIndex = medianOfMedians(arr, low, high);
    // int pivotIndex = MED3(arr, low, (low + high) / 2, high);
    int pivot = arr[pivotIndex];
    // int pivot = medianOfMedians(arr, low, high); // >> Error!
    // int pivot = arr[MED3(arr, low, (low + high) / 2, high)];
    // int pivot = arr[choosePivotIndex(arr, low, high)];
    int i = low - 1, j = high + 1;

    while (true) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);

        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    return j;

    // while (i <= j) {
    //     while (arr[i] < pivot) i++;
    //     while (arr[j] > pivot) j--;

    //     if (i < j) swap(arr[i++], arr[j--]);
    //     else i++;
    // }
    // return j;
}

void lomutoQuickSortRecur(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = lomutoPartition(arr, low, high);
        lomutoQuickSortRecur(arr, low, pivotIndex - 1);
        lomutoQuickSortRecur(arr, pivotIndex + 1, high);
    }
}

void hoareQuickSortRecur(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = hoarePartition(arr, low, high);
        hoareQuickSortRecur(arr, low, pivotIndex);
        hoareQuickSortRecur(arr, pivotIndex + 1, high);
    }
}

void lomutoQuickSort(int arr[], int n) { 
    lomutoQuickSortRecur(arr, 0, n - 1);
}

void hoareQuickSort(int arr[], int n) {
    hoareQuickSortRecur(arr, 0, n - 1);
}

int MED3(int arr[], int low, int mid, int high) {
    // int a = arr[low], b = arr[mid], c = arr[high];
    // if (a < b) {
    //     if (b < c) return mid;
    //     else return a < c ? high : low;
    // } else {
    //     if (b > c) return mid;
    //     else return a > c ? high : low;
    // }

    return (arr[low] < arr[mid]) ?
           (arr[mid] < arr[high] ? mid : low) :
           (arr[low] < arr[high] ? low : high);
}

int choosePivotIndex(int arr[], int low, int high) {
    int n = high - low + 1;
    int mid = low + (high - low) / 2;
    if (n > 7) {
        if (n > 40) {
            int d = n / 8;

            low = MED3(arr, low, low + d, low + 2*d);
            mid = MED3(arr, mid - d, mid, mid + d);
            high = MED3(arr, high - 2*d, high - d, high);
        }
        mid = MED3(arr, low, mid, high);
    }
    return mid;
}


int findMedianIndex(int arr[], int low, int high) {
    // Insertion sort
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= low && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
    return low + (high - low + 1) / 2;
}

int medianOfMedians(int arr[], int low, int high) {
    int medianIndex;
    int n = high - low + 1;

    // 배열의 크기가 5보다 작거나 같으면 간단히 정렬하고 중앙값 반환
    if (n <= 5)
        return findMedianIndex(arr, low, high);

    // 배열을 5개씩의 그룹으로 나누고, 각 그룹의 중앙값을 찾음
    int groupSize = 5;
    int groupCnt = (n + groupSize - 1) / groupSize;     // 올림
    int* medians = new int[groupCnt];
    for (int i = 0; i < groupCnt; ++i) {
        int groupLow = low + i * 5;
        int groupHigh = min(low + (i + 1) * 5 - 1, high);
        medianIndex = medianOfMedians(arr, groupLow, groupHigh);
        medians[i] = arr[medianIndex];
    }

    // 중앙값의 중앙값을 재귀적으로 찾음
    medianIndex = findMedianIndex(medians, 0, groupCnt - 1);
    delete[] medians;
    return medianIndex;
}