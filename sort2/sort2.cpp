#include "sort2.h"

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
inline int min(int a, int b) { return (a < b)? a: b; }
inline int max(int a, int b) { return (a < b)? b: a; }
inline int ceil(int a, int b) { return (a + b - 1) / b; }

/////////////////////////////////////////////////////////////////////
// Bubble Sort and Its Variations

void bubbleSort(int arr[], int low, int high) {
    for (int i = high; i > low ; i--)
        for (int j = low; j < i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);

    // for (int i = 0; i < high - low; i++)
    //     for (int j = low; j < high - i; j++)
    //         if (arr[j] > arr[j + 1])
    //             swap(arr[j], arr[j + 1]);

    // while (low < high) {
    //     for (int j = low; j < high; j++)
    //         if (arr[j] > arr[j + 1])
    //             swap(arr[j], arr[j + 1]);
    //     high--;
    // }
}

void bubbleSortRecursive(int arr[], int low, int high) {
    if (low >= high) return;
    for (int i = low; i < high; i++)
        if (arr[i] > arr[i + 1])
            swap(arr[i], arr[i + 1]);
    bubbleSortRecursive(arr, low, high - 1);
}

void bubbleSortOptimized(int arr[], int low, int high) {
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

    // bool isSwapped = true;
    // while (isSwapped) {
    //     isSwapped = false;
    //     for (int i = low; i < high; i++)
    //         if (arr[i] > arr[i + 1]) {
    //             swap(arr[i], arr[i + 1]);
    //             isSwapped = true;
    //         }
    //     high--;
    //     if (!isSwapped) break;
    // }
}

void cocktailSort(int arr[], int low, int high) {
    bool isSwapped = true;
    while (isSwapped) {
        isSwapped = false;
        for (int j = low; j < high; j++)
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        high--;
        if (!isSwapped) break;

        isSwapped = false;
        for (int j = high - 1; j >= low; j--)
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        low++;
    }
}

void combSort(int arr[], int low, int high) {
    bool isSwapped = true;
    int gap = high - low + 1;
    double shrinkFactor = 1.3; // 일반적인 축소 비율

    while (isSwapped || gap > 1) {
        isSwapped = false;
        gap = max(1, gap / shrinkFactor);
        for (int j = low; j + gap <= high; j++)
            if (arr[j] > arr[j + gap]) {
                swap(arr[j], arr[j + gap]);
                isSwapped = true;
            }
        if (!isSwapped) break;
    }
}

/////////////////////////////////////////////////////////////////////
// Selection Sort and Its Variations

void selectionSort(int arr[], int low, int high) {
    // 최소값을 찾아서 앞으로 보냄
    for (int i = low; i < high; i++) {
        int minIndex = i;
        for (int j = i + 1; j <= high; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        if (minIndex != i) swap(arr[minIndex], arr[i]);
    }

    // 최대값을 찾아서 뒤로 보냄
    // for (int i = high; i > low; i--) {
    //     int maxIndex = i;
    //     for (int j = low; j < i; j++)
    //         if (arr[j] > arr[maxIndex])
    //             maxIndex = j;
    //     if (maxIndex != i) swap(arr[maxIndex], arr[i]);
    // }
}

/////////////////////////////////////////////////////////////////////
// Insertion Sort and Its Variations

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= low && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }

    // for (int i = low + 1; i <= high; i++) {
    //     int key = arr[i];
    //     int j = i - 1;
    //     while (j >= low && arr[j] > key) {
    //         arr[j + 1] = arr[j];
    //         j--;
    //     }
    //     arr[j + 1] = key;
    // }
}

int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

void binaryInsertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int pos = binarySearch(arr, low, i - 1, key);

        for (int j = i - 1; j >= pos; j--)
            arr[j + 1] = arr[j];
        arr[pos] = key;
    }
}

void shellSort(int arr[], int low, int high) {
    int n = high - low + 1;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = low + gap; i <= high; i++) {
            int key = arr[i], j;
            for (j = i - gap; j >= low && arr[j] > key; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = key;
        }
    }
}

void shellSortKnuth(int arr[], int low, int high) {
    // [Knuth] 1, 4, 13, 40, 121, 363, 1093, ...
    int gap = 1, n = high - low + 1;
    while (gap < n / 3) gap = gap * 3 + 1;

    while (gap >= 1) {
        for (int i = low + gap; i <= high; i++) {
            int key = arr[i], j;
            for (j = i - gap; j >= low && arr[j] > key; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = key;
        }
        gap /= 3;
    }
}

void cycleSort(int arr[], int low, int high) {
    int writes = 0;

    // 모든 요소에 대해 사이클 찾기
    for (int cycleStart = low; cycleStart <= high; cycleStart++) {
        int item = arr[cycleStart];
        int pos = cycleStart;

        // 올바른 위치 찾기
        for (int i = cycleStart + 1; i <= high; i++)
            if (arr[i] < item)
                pos++;

        // 이미 제자리에 있는 경우 건너뛰기
        if (pos == cycleStart)
            continue;

        // 사이클 교환
        while (item == arr[pos])
            pos++;
        swap(arr[pos], item);
        writes++;

        // 나머지 사이클 요소 교환
        while (pos != cycleStart) {
            pos = cycleStart;
            for (int i = cycleStart + 1; i <= high; i++)
                if (arr[i] < item)
                    pos++;
            while (item == arr[pos])
                pos++;
            swap(arr[pos], item);
            writes++;
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Quick Sort and Its Variations

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
    return { i - 1, i + 1 };    // default: i
}

void quickSortLomuto(int arr[], int low, int high) {
    if (low >= high) return;

    pii pivotIndex = lomutoPartition(arr, low, high);
    quickSort(arr, low, pivotIndex.high);
    quickSort(arr, pivotIndex.low, high);
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
    return { j, j + 1 };    // default: j
}

void quickSortHoare(int arr[], int low, int high) {
    if (low >= high) return;

    pii pivotIndex = hoarePartition(arr, low, high);
    quickSort(arr, low, pivotIndex.high);
    quickSort(arr, pivotIndex.low, high);
}

// int partition(int arr[], int low, int high, int pivotIndex) {
//     int pivot = arr[pivotIndex];
//     swap(arr[pivotIndex], arr[high]);
//     int i = low - 1;

//     for (int j = low; j < high; j++)
//         if (arr[j] <= pivot)
//             swap(arr[++i], arr[j]);

//     swap(arr[++i], arr[high]);
//     return i;
// }

// void quickSort(int arr[], int low, int high) {
//     if (low >= high) return;
//     int mid = low + (high - low) / 2;
//     int pivotIndex = partition(arr, low, high, mid);

//     quickSort(arr, low, pivotIndex - 1);
//     quickSort(arr, pivotIndex + 1, high);
// }

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
        int key = arr[i], j;
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

    // 중앙값의 중앙값 구하기 (재귀적으로 호출)
    return medianOfMedians(medians, 0, groupCnt - 1);
    // int median = medianOfMedians(medians, 0, groupCnt - 1);
    // // delete[] medians;
    // return median;

    // 중앙값의 중앙값 구하기 (선형 시간 알고리즘 사용)
    // return select(medians, 0, groupCnt - 1, groupCnt / 2);
}

// Hoare Partition
int partition(int arr[], int low, int high) {
    // int pivot = arr[(low + high) / 2];  // default
    // int pivot = arr[MED3(arr, low, (low + high) / 2, high)];
    // int pivot = arr[choosePivotIndex(arr, low, high)];
    int pivot = medianOfMedians(arr, low, high);
    int i = low - 1, j = high + 1;

    while (true) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);

        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    return j;    // default: j
}

// Quick Sort with Hoare Partition
void quickSort(int arr[], int low, int high) {
    if (low >= high) return;
    int pivotIndex = partition(arr, low, high);

    quickSort(arr, low, pivotIndex);
    quickSort(arr, pivotIndex + 1, high);
}


/////////////////////////////////////////////////////////////////////
// Merge Sort and Its Variations

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
    if (low >= high) return;
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
}

void mergeSortBottomUp(int arr[], int low, int high) {
    int n = high - low + 1;
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            merge(arr + low, left, mid, right);
        }
    }
}

void hybridSort(int arr[], int low, int high, int threshold) {
    if (high - low <= threshold) {
        insertionSort(arr, low, high);
    } else {
        int mid = low + (high - low) / 2;
        hybridSort(arr, low, mid, threshold);
        hybridSort(arr, mid + 1, high, threshold);
        merge(arr, low, mid, high);
    }
}

void heapSort(int arr[], int low, int high) {}

/////////////////////////////////////////////////////////////////////
// Non-comparision Sorting Algorithms

void bucketSort(int arr[], int low, int high) {
    // 입력 범위 내의 최댓값과 최솟값 찾기
    int maxValue = arr[low];
    int minValue = arr[low];
    for (int i = low + 1; i <= high; ++i) {
        maxValue = max(maxValue, arr[i]);
        minValue = min(minValue, arr[i]);
    }

    // 2차원 배열로 버킷 생성 (첫번째 인덱스에 개수 저장)
    int n = high - low + 1;
    int bucketSize = (maxValue - minValue) / n;
    int bucketCnt = ceil(maxValue - minValue, bucketSize);
    int buckets[bucketCnt][n + 1];  // 두번째 인덱스부터 배열 저장
    for (int i = 0; i < bucketCnt; i++) buckets[i][0] = 0;

    // 각 요소를 해당 버킷에 삽입
    for (int i = low; i <= high; ++i) {
        int bucketIdx = (arr[i] - minValue) / bucketSize;
        buckets[bucketIdx][0]++;    // 첫 번째 요소에 개수 저장
        buckets[bucketIdx][buckets[bucketIdx][0]] = arr[i];
    }

    // 각 버킷 내부 정렬 (삽입 정렬)
    for (int i = 0; i < bucketCnt; ++i)
        insertionSort(buckets[i], 1, buckets[i][0]);

    // 정렬된 버킷들을 다시 원래 배열에 병합
    int index = low;
    for (int i = 0; i < bucketCnt; ++i)
        for (int j = 1; j <= buckets[i][0]; j++)
            arr[index++] = buckets[i][j];
}

void countingSort(int arr[], int low, int high) {
    int base = 1'000'000;       // 0 <= arr[j] < base (MAX_NUM)
    int count[base];
    int sorted[high - low + 1];

    for (int j = 0; j < base; j++) count[j] = 0;                        // initialize
    for (int j = low; j <= high; j++) count[arr[j]]++;                  // count
    for (int j = 1; j < base; j++) count[j] += count[j - 1];            // accumulate
    for (int j = high; j >= low; j--) sorted[--count[arr[j]]] = arr[j]; // sort
    for (int j = low; j <= high; j++) arr[j] = sorted[j - low];         // copy
}

void radixSort10(int arr[], int low, int high) {
    int base = 10;              // 0 <= arr[j] < base^digits (= 10^6)
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
    int base = 256;             // 0 <= arr[j] < 2^32 (= 256^4)
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