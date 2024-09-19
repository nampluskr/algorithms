#include "binary_search.h"

inline int abs(int x) { return ((x) > 0) ? (x) : -(x); }

int binarySearch(const int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) low = mid + 1;
        else if (target < arr[mid]) high = mid - 1;
        else return mid;
    }
    return -1;
}

int lowerBound(const int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int upperBound(const int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= target) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int findNearest(const int arr[], int n, int target) {
    int low = 0, high = n - 1;
    int minIdx = 0, minDist = abs(arr[0] - target);

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int dist = abs(arr[mid] - target);
        if (dist < minDist) minIdx = mid, minDist = dist;

        if (arr[mid] < target) low = mid + 1;
        else if (target < arr[mid]) high = mid - 1;
        else return mid;
    }
    return minIdx;
}