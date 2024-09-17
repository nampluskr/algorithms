#include <cstdio>

void print(int arr[], int n) {
    printf(">> ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
int min(int a, int b) { return (a < b)? a: b; }

// 5개 이하의 요소를 Insertion Sort로 정렬하고 중앙값 반환
int findMedianOfFive(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return arr[low + 2]; // 5개 요소의 중앙값은 인덱스 2
}

// Median-of-Medians 함수
int medianOfMedians(int arr[], int low, int high) {
    int n = high - low + 1;

    if (n <= 5) {
        return findMedianOfFive(arr, low, high);
    }

    // 5개씩 그룹으로 나누고, 각 그룹의 중앙값을 찾아 새로운 배열에 저장
    int numGroups = (n + 4) / 5;
    int medians[numGroups];
    for (int i = 0; i < numGroups; i++) {
        int groupLow = low + i * 5;
        int groupHigh = min(low + (i + 1) * 5 - 1, high);
        medians[i] = findMedianOfFive(arr, groupLow, groupHigh);
    }
    // 중앙값의 중앙값을 재귀적으로 찾음
    return medianOfMedians(medians, 0, numGroups - 1);
}


// // Median-of-Medians 함수
// int medianOfMedians(int arr[], int low, int high) {
//     int n = high - low + 1;

//     if (n <= 5) {
//         return findMedianOfFive(arr, low, high);
//     }

//     // 5개씩 그룹으로 나누고, 각 그룹의 중앙값을 찾아 새로운 배열에 저장
//     int numGroups = (n + 4) / 5;
//     int* medians = new int[numGroups];
//     for (int i = 0; i < numGroups; i++) {
//         int groupLow = low + i * 5;
//         int groupHigh = min(low + (i + 1) * 5 - 1, high);
//         medians[i] = findMedianOfFive(arr, groupLow, groupHigh);
//     }

//     // 중앙값의 중앙값을 재귀적으로 찾음
//     int median = medianOfMedians(medians, 0, numGroups - 1);
//     delete[] medians;
//     return median;
// }

int hoarePartition(int arr[], int low, int high, int pi) {
    // 피벗을 배열의 마지막 위치로 이동
    swap(arr[pi], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort 함수
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = medianOfMedians(arr, low, high); // 피벗 선택
        pi = hoarePartition(arr, low, high, pi);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    print(arr, n);
    quickSort(arr, 0, n - 1);
    print(arr, n);

    return 0;
}