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
    // int pivotIndex = choosePivotIndex(arr, low, high);
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
    int pivot = arr[(low + high) / 2];  // default
    // int pivot = arr[MED3(arr, low, (low + high) / 2, high)];
    // int pivot = arr[choosePivotIndex(arr, low, high)];
    // int pivot = medianOfMedians(arr, low, high);
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


int medianOfFive(int arr[], int low, int high) {
    // Insertion sort
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= low && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
    return arr[(low + high) / 2];
}

int medianOfMedians(int arr[], int low, int high) {
    int n = high - low + 1;

    // 배열의 크기가 5보다 작거나 같으면 간단히 정렬하고 중앙값 반환
    if (n <= 5)
        return medianOfFive(arr, low, high);

    // 배열을 5개씩의 그룹으로 나누고, 각 그룹의 중앙값을 찾음
    int groupSize = 5;
    int groupCnt = (n + groupSize - 1) / groupSize;     // 올림
    int medians[groupCnt];
    // int* medians = new int[groupCnt];
    for (int i = 0; i < groupCnt; i++) {
        int groupLow = low + i * groupSize;
        int groupHigh = min(low + (i + 1) * groupSize - 1, high);
        medians[i] = medianOfFive(arr, groupLow, groupHigh);
    }

    // 중앙값의 중앙값을 재귀적으로 찾음
    int median = medianOfMedians(medians, 0, groupCnt - 1);
    // delete[] medians;
    return median;
}

/////////////////////////////////////////////////////////////////////
#if 1   // [Gemini]
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int arr1[n1], arr2[n2];           // 임시 배열 생성

    // 임시 배열에 값 복사
    for (int i = 0; i < n1; i++) arr1[i] = arr[low + i];
    for (int j = 0; j < n2; j++) arr2[j] = arr[mid + 1 + j];

    // 두 개의 정렬된 부분 배열을 합병
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) arr[k] = arr1[i++];
        else arr[k] = arr2[j++];
        k++;
    }

    // 남은 요소 복사
    while (i < n1) arr[k++] = arr1[i++];
    while (j < n2) arr[k++] = arr2[j++];
}

void mergeSortRecur(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSortRecur(arr, low, mid);
        mergeSortRecur(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void bottomUpMergeSort(int arr[], int n) {
    for (int size = 1; size < n; size = 2 * size) {
        for (int low = 0; low < n - size; low += 2 * size) {
            int mid = low + size - 1;
            int high = min(low + 2 * size - 1, n - 1);
            merge(arr, low, mid, high);
        }
    }
}
#else
void merge(int arr1[], int n1, int arr2[], int n2, int aux[]) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) aux[k++] = arr1[i++];
        else aux[k++] = arr2[j++];
    }
    while (i < n1) { aux[k++] = arr1[i++]; }
    while (j < n2) { aux[k++] = arr2[j++]; }
}

void mergeSortRecur(int arr[], int low, int high) {
    if (low >= high) return;

    int mid = low + (high - low) / 2;
    mergeSortRecur(arr, low, mid);
    mergeSortRecur(arr, mid + 1, high);

    int aux[high - low + 1];
    merge(arr + low, mid - low + 1, arr + mid + 1, high - mid, aux);
    for (int i = low, j = 0; i <= high; i++, j++) arr[i] = aux[j];
}

void bottomUpMergeSort(int arr[], int n) {
    // int *aux = new int[n]; // 임시 배열 생성
    int aux[n];

    // 부분 배열의 크기가 1부터 시작하여 배열 전체 크기까지 증가
    for (int size = 1; size < n; size = size * 2) {
        // 각 부분 배열을 합병
        for (int low = 0; low < n - size; low += 2 * size) {
            int mid = low + size - 1;
            int high = min(low + 2 * size - 1, n - 1);
            merge(arr + low, mid - low + 1, arr + mid + 1, high - mid, aux + low);
            // 합병된 결과를 다시 원래 배열에 복사
            for (int i = low; i <= high; i++) arr[i] = aux[i];
        }
    }
    // delete[] aux; // 임시 배열 메모리 해제
}
#endif

void mergeSort(int arr[], int n) {
    mergeSortRecur(arr, 0, n - 1);
}


/////////////////////////////////////////////////////////////////////
void countingSort(int arr[], int n, int maxNumber) {
    int base = maxNumber;		    // 0 <= arr[j] < base (MAX_NUM)
    // int* count = new int[base];
    // int* sorted = new int[n];
    int count[base];
    int sorted[n];

    for (int j = 0; j < base; j++) count[j] = 0;				        // initialize
    for (int j = 0; j < n; j++) count[arr[j]]++;				        // count
    for (int j = 1; j < base; j++) count[j] += count[j - 1];	        // accumulate
    for (int j = n - 1; j >= 0; j--) sorted[--count[arr[j]]] = arr[j];  // sort
    for (int j = 0; j < n; j++) { arr[j] = sorted[j]; }			        // copy

    // delete[] count, sorted;
}

void radixSort10(int arr[], int n) {
    int base = 10;			    // 0 <= arr[j] < base^digits (= 10^6)
    int decimal = 1;
    // int* count = new int[base];
    // int* sorted = new int[n];
    int count[base];
    int sorted[n];

    // counting sort in base 10 for 10^i digit
    for (int i = 0; i < 6; i++, decimal *= 10) {

        for (int j = 0; j < base; j++) count[j] = 0;
        for (int j = 0; j < n; j++) count[arr[j] / decimal % base]++;
        for (int j = 1; j < base; j++) count[j] += count[j - 1];
        for (int j = n - 1; j >= 0; j--) sorted[--count[arr[j] / decimal % base]] = arr[j];
        for (int j = 0; j < n; j++) arr[j] = sorted[j];
    }
    // delete[] count, sorted;
}

void radixSort256(int arr[], int n) {
    int base = (1 << 8);        // 0 <= arr[j] < 2^32 (= 256^4)
    int mask = base - 1;
    // int* count = new int[base];
    // int* sorted = new int[n];
    int count[base];
    int sorted[n];

    // counting sort in base 256 for 256^i digit
    for (int i = 0; i < 32; i += 8) {

        for (int j = 0; j < base; j++) count[j] = 0;
        for (int j = 0; j < n; j++) count[(arr[j] >> i) & mask]++;
        for (int j = 1; j < base; j++) count[j] += count[j - 1];
        for (int j = n - 1; j >= 0; j--) sorted[--count[(arr[j] >> i) & mask]] = arr[j];
        for (int j = 0; j < n; j++) arr[j] = sorted[j];
    }
    // delete[] count, sorted;
}