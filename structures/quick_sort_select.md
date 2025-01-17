## Quick Sort / Select

```cpp
#include <stdio.h>

#define MAX_NUM 100

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

// Lomuto Partitioning
int partition(int arr[], int first, int last) {
    int pivot = first;
    int i = first;
    int j = last;

    while (i < j) {
        while (arr[i] <= arr[pivot] && i < last) { i++; }
        while (arr[j] > arr[pivot]) { j--; }
        if (i < j) { swap(arr[i], arr[j]); }
    }
    swap(arr[pivot], arr[j]);
    return j;
}

// O(n log n)
void quickSort(int arr[], int first, int last) {
    if (first < last) {
        int j = partition(arr, first, last);
        quickSort(arr, first, j - 1);
        quickSort(arr, j + 1, last);
    }
}


// O(n)
int quickSelect(int arr[], int first, int last, int k) {
    if (first < last) {
        int j = partition(arr, first, last);
        if (k < j) return quickSelect(arr, first, j - 1, k);
        else if (j < k) return quickSelect(arr, j + 1, last, k);
        else return arr[j];
    }
    return arr[first];
}

void print(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    int arr1[MAX_NUM] = { 10, 11, 12, 3, 2, 1, 5, 4, 7, 8, 9, 6 };
    int arr2[MAX_NUM] = { 10, 11, 12, 3, 2, 1, 5, 4, 7, 8, 9, 6 };
    int n = 12;

    print(arr1, n);
    quickSort(arr1, 0, n - 1);
    print(arr1, n);

    printf("\n");
    print(arr2, n);
    int topk = quickSelect(arr2, 0, n - 1, 1);  // 2nd smallest
    printf("topk = %d\n", topk);
    print(arr2, n);

    return 0;
}
```
