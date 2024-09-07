```cpp
#if 1
#include <cstdio>

template<typename T>
inline void swap(T& a, T& b) { T temp = a; a = b; b = temp; }


// https://www.geeksforgeeks.org/quick-sort-algorithm/
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int medianSelect(int arr[], int low, int high) {
    if (low == high) return arr[low];

    int mid = (low + high) / 2;
    while (low <= high) {
        int pivotIndex = partition(arr, low, high);
        if (pivotIndex < mid) low = pivotIndex + 1;
        else if (mid < pivotIndex) high = pivotIndex - 1;
        else return arr[pivotIndex];
    }
    return -1;
}

void quickSelect(int arr[], int low, int high, int k) {
    if (low == high) return;

    int pivotIndex = partition(arr, low, high);
    if (k < pivotIndex) quickSelect(arr, low, pivotIndex - 1, k);
    else if (pivotIndex < k) quickSelect(arr, pivotIndex + 1, high, k);
    else return;
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) return;

    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
} 

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int findMedian(vector<int>& nums) {
    priority_queue<int, vector<int>, less<int>> maxHeap; // Stores the larger half of elements
    priority_queue<int, vector<int>, greater<int>> minHeap; // Stores the smaller half of elements

    for (int num : nums) {
        maxHeap.push(num);

        // Balance heaps by moving top element from max heap to min heap if necessary
        if (maxHeap.size() > minHeap.size()) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        // Calculate median based on heap sizes
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2;
        }
        else {
            // Max heap is always larger, so its top element is the median
            return maxHeap.top();
        }
    }

    return -1; // Shouldn't reach here in a practical scenario as you'd have elements to process
}


int main() {
    int arr[] = { 12, 6, 1, 15, 9, 3, 2, 20, 50, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 6;

    printArray(arr, n);

    //quickSelect(arr, 0, n - 1, k - 1);
    //printArray(arr, n);
    //printf(">> %d-th smallest element: %d\n", k, arr[k - 1]);

    //k = 8;
    //quickSelect(arr, 0, n - 1, k - 1);
    //printArray(arr, n);
    //printf(">> %d-th smallest element: %d\n", k, arr[k - 1]);

    //quickSort(arr, 0, n - 1);
    //printArray(arr, n);

    int median = medianSelect(arr, 0, n - 1);
    printf(">> Median: %d\n", median);
    printArray(arr, n);

    return 0;
}
#endif
```

원소가 실시간으로 추가되는 배열의 중간값(median)을 계산하는 것은 효율적인 솔루션이 필요한 문제입니다!  

여기에는 insert 연산 후, 배열의 새로운 median 값을 빠르게 찾는 방법에 대한 아이디어를 설명해 드리겠습니다.

1. Priority Queue:


개념:
 우선순위 큐(priority queue)는 항상 가장 큰 또는 가장 작은 요소를 최전방에 보관하는 데이터 구조입니다.



적용 방법: 배열의 원소들을 우선순위 큐에 추가합니다. 큐의 크기는  n/2 + 1 로 설정됩니다(여기서 n은 배열의 크기).  우선순위 큐가 항상 가장 큰 n/2 + 1 개의 요소를 저장하므로, 이 경우에 대한 median 값이 항상 우선순위 큐의 중간 위치에 있습니다.



시간 복잡도:



배열 원소 추가: O(log n)

median 확인: O(1)



2. 투 포인터 (Two Pointers)


개념: 두 포인터를 활용하여, 힙에 더 이상 적합하지 않은 원소들을 제거하면서 배열의 중간 값을 찾습니다.



적용 방법:



배열에서 최대 n/2 + 1 개의 요소를 선택해 저장합니다. 이 과정이 복잡할 수 있습니다.



3. QuickSelect Algorithm:


개념: 빠른 정렬 알고리즘인 Quicksort에서 median 값을 찾는 변형입니다.

적용 방법: 배열의 원소들을 중간값을 찾기 위한 목적으로 재정렬하는데,  median 찾기 연산이 필요합니다.

사항:


효율성: 각 알고리즘은 특정 상황에서 유리할 수 있습니다. 



우선순위 큐는 추가된 원소를 처리하기 위한 가장 간단하고 직관적인 방법입니다. 

투 포인터와 QuickSelect는 배열의 크기가 증가하면 더 효율적일 수 있습니다.



공간 복잡도: 우선순위 큐 알고리즘은 추가 원소를 저장하기 위해 O(n) 공간 복잡도를 가지지만, 투 포인터 알고리즘은 배열의 크기를 유지하며 작동할 수 있도록 합니다.



선택 알고리즘:
어떤 알고리즘을 선택해야 할까요? 


실시간 성능이 중요하고 데이터가 많은 경우: 우선순위 큐 또는 투 포인터를 사용하는 것이 좋습니다.



데이터 크기가 작거나 중간값을 빠르게 찾는 것에 더 큰 집중력 필요 시:  투 포인터 알고리즘은 효율적입니다.
