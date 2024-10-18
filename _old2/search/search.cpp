#include "search.h"

#include <cstdio>
#include <cmath>

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
inline int min(int a, int b) { return (a < b)? a: b; }
inline int max(int a, int b) { return (a < b)? b: a; }
inline int ceil(int a, int b) { return (a + b - 1) / b; }


void printArray(int arr[], int low, int high) {
    printf(">> ");
    for (int i = low; i < high; i++)
        printf("%d, ", arr[i]);
    printf("%d\n", arr[high]);
}

/////////////////////////////////////////////////////////////////////
// Linear and Its Variations

int linearSearch(int arr[], int low, int high, int target) {
    // for 문 사용
    for (int i = low; i <= high; i++)
        if (arr[i] == target)
            return i;   // 타겟 값을 찾으면 인덱스 반환
    return -1;          // 타겟 값을 찾지 못하면 -1 반환

    // while 문 사용
    // int i = low;
    // while (i <= high) {
    //     if (arr[i] == target) return i;
    //     i++;
    // }
    // return -1;
}

int linearSearchRecur(int arr[], int low, int high, int target) {
    // forward search
    if (low > high) return -1;
    if (arr[low] == target) return low;
    return linearSearchRecur(arr, low + 1, high, target);

    // backward search
    // if (low > high) return -1;
    // if (arr[high] == target) return high;
    // return linearSearchRecur(arr, low, high - 1, target);
}

int sentinelSearch(int arr[], int low, int high, int target) {
    int last = arr[high];
    arr[high] = target;     // Element to be searched is placed at the last index

    int i = low;
    while (arr[i] != target) i++;
    arr[high] = last;       // 센티널 값 복원

    return (i < high) ? i : -1;
}

int tranpositionSearch(int arr[], int low, int high, int target) {
    for (int i = low; i <= high; i++) {
        // If target is found, then swap the element with it's previous index
        if (arr[i] == target) {
            if (i == 0) return i; // If target is first element
            swap(arr[i], arr[i - 1]);
            return i;
        }
    }
    return -1;
}

int searchMoveToFront(int arr[], int low, int high, int target) {
    for (int i = low; i <= high; i++) {
        // If target is found, then swap the element with 0-th index
        if (arr[i] == target) {
            swap(arr[i], arr[low]);
            return i;
        }
    }
    return -1;
}



/////////////////////////////////////////////////////////////////////
// Binary and Its Variations

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i], j;
        for (j = i - 1; j >= low && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
}

int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int binarySearchRecur(int arr[], int low, int high, int target) {
    if (low > high) return -1;

    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) return binarySearchRecur(arr, mid + 1, high, target);
    else return binarySearchRecur(arr, low, mid - 1, target);
}

int lowerBound(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int lowerBoundRecur(int arr[], int low, int high, int target) {
    if (low > high) return low;

    int mid = low + (high - low) / 2;
    if (arr[mid] < target) return lowerBoundRecur(arr, mid + 1, high, target);
    else return lowerBoundRecur(arr, low, mid - 1, target);
}

int upperBound(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] <= target) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int upperBoundRecur(int arr[], int low, int high, int target) {
    if (low > high) return low;

    int mid = low + (high - low) / 2;
    if (arr[mid] <= target) return upperBoundRecur(arr, mid + 1, high, target);
    else return upperBoundRecur(arr, low, mid - 1, target);
}

// Parametric Search
bool check(int arr[], int x, int target) {
    return target <= arr[x];
}

int parametricSearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(arr, mid, target))
            high = mid - 1;
        else
            low = mid + 1;
    }
    return low;
}
