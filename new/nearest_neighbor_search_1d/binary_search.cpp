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



int main() {
    std::vector<int> arr = {2, 5, 8, 10, 12};
    int target = 6;

    // int closest = findClosest2(arr, target, 0, arr.size() - 1);
    int closest = findClosest3(arr, target);
    std::cout << "Target: " << target << ", Closest Element: " << closest << std::endl;

    return 0;
}