#if 0
#include <iostream>
#include <vector>

// lower_bound 함수 (앞서 구현한 함수)
int lower_bound(int arr[], int left, int right, int target) {
    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

// 가장 가까운 값 찾기 함수
int find_closest(int arr[], int n, int target) {
    int idx = lower_bound(arr, 0, n, target);

    // target이 배열의 모든 값보다 큰 경우
    if (idx == n) {
        return n - 1;
    }

    // target이 배열의 모든 값보다 작은 경우
    if (idx == 0) {
        return 0;
    }

    // target과 가장 가까운 값 비교
    if (target - arr[idx - 1] <= arr[idx] - target) {
        return idx - 1;
    } else {
        return idx;
    }
}

int main() {
    int arr[] = {1, 3, 5, 8, 9};
    int target = 7;
    int n = sizeof(arr) / sizeof(arr[0]);

    int closest = find_closest(arr, n, target);
    std::cout << "Closest value: " << arr[closest] << std::endl;

    return 0;
}
#endif