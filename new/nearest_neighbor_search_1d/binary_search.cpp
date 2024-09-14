#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findClosest1(const std::vector<int>& arr, int target) {
  int left = 0;
  int right = arr.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2; // Prevent potential overflow

    if (arr[mid] == target) {
        return arr[mid];      // Exact match found
    } else if (target < arr[mid]) {
        right = mid - 1;      // Search in the left half
    } else {
        left = mid + 1;       // Search in the right half
    }
  }
  // Either target not found or reached the edge of the array
  return (abs(arr[left - 1] - target) < abs(arr[left] - target)) ? arr[left - 1] : arr[left];
}


int findClosest2(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return (abs(arr[left - 1] - target) < abs(arr[left] - target)) ? arr[left - 1] : arr[left]; 
    }

    int mid = left + (right - left) / 2;  // Prevent potential overflow

    if (arr[mid] == target) {
        return arr[mid]; // Exact match found
    } else if (target < arr[mid]) {
        return findClosest2(arr, target, left, mid - 1); // Search in the left half
    } else {
        return findClosest2(arr, target, mid + 1, right); // Search in the right half
    }
}

int findClosest3(const std::vector<int>& arr, int target) {
    auto it = std::lower_bound(arr.begin(), arr.end(), target);

    // target보다 큰 값이 없다면 마지막 원소가 가장 가까운 값
    if (it == arr.end()) {
        return arr[arr.size() - 1];
    }

    // target보다 작은 값이 없다면 첫 번째 원소가 가장 가까운 값
    if (it == arr.begin()) {
        return arr[0];
    }

    // 이전 원소와의 차이와 현재 원소와의 차이를 비교하여 더 가까운 값을 반환
    int left = it - arr.begin() - 1;
    int right = it - arr.begin();
    return std::abs(arr[left] - target) < std::abs(arr[right] - target) ? arr[left] : arr[right];
}

int lower_bound(int arr[], int left, int right, int target) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}


int main() {
    std::vector<int> arr = {2, 5, 8, 10, 12};
    int target = 20;

    int closest = findClosest3(arr, target);
    // int closest = findClosest2(arr, target, 0, arr.size() - 1);
    std::cout << "Target: " << target << ", Closest Element: " << closest << std::endl;

    return 0;
}
#endif