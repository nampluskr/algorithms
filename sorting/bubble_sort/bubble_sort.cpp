#include <cstdio>

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

void print(int arr[], int n) {
    printf(">> ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 기본 버블 정렬
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
}

// 개선 버블 정렬 (Optimized Bubble Sort)
// 한 번의 반복에서 교환이 발생하지 않았다면 더 이상 반복할 필요가 없다는 점을 이용
void bubbleSortOptimized(int arr[], int n) {
    bool isSwapped;
    for (int i = 0; i < n - 1; i++) {
        isSwapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }
        // 한 번의 반복에서 교환이 발생하지 않았다면 이미 정렬된 상태
        if (!isSwapped) break;
    }
}

// 칵테일 정렬 (Cocktail Shaker Sort)
// 버블 정렬을 양방향으로 진행하여 효율성을 높이는 방법입니다.
void cocktailSort(int arr[], int n) {
    bool isSwapped = true;
    int start = 0, end = n - 1;

    while (isSwapped) {
        isSwapped = false;

        // 왼쪽에서 오른쪽으로 스캔
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        }
        // 만약 교환이 발생하지 않았다면 이미 정렬된 상태
        if (!isSwapped)
            break;

        isSwapped = false;
        end--;

        // 오른쪽에서 왼쪽으로 스캔
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        }
        start++;
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);

    print(arr, n);
    // bubbleSort(arr, n);
    // bubbleSortOptimized(arr, n);
    cocktailSort(arr, n);
    print(arr, n);
    return 0;
}