#include <cstdio>

template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<typename T>
void print(const T arr[], int n) {
    printf(">> ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 기본 버블 정렬
// 인접한 두 원소를 비교하여 큰 값을 뒤로 이동
// template<typename T>
// void bubbleSort(T arr[], int n) {
//     for (int i = n - 1; i > 0; i--)
//         for (int j = 0; j < i; j++)
//             if (arr[j] > arr[j+1])
//                 swap(arr[j], arr[j+1]);
// }

// template<typename T>
// void bubbleSort(T arr[], int n) {
//     for (int i = 0; i < n - 1; i++)
//         for (int j = 0; j < n - i - 1; j++)
//             if (arr[j] > arr[j+1])
//                 swap(arr[j], arr[j+1]);
// }


// 개선 버블 정렬 (Optimized Bubble Sort)
// 한 번의 반복에서 교환이 발생하지 않았다면 더 이상 반복할 필요가 없다는 점을 이용
template<typename T>
void bubbleSortOptimized(T arr[], int n) {
    bool isSwapped;
    for (int i = n - 1; i > 0; i--) {
        isSwapped = false;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }
        // 교환이 발생하지 않았다면 이미 정렬된 상태
        if (!isSwapped) break;
    }
}

template<typename T>
void bubbleSort(T arr[], int n) {
    bool isSwapped = true;
    int hi = n - 1;

    while (isSwapped) {
        isSwapped = false;
        for (int i = 0; i < hi; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        }
        // 교환이 발생하지 않았다면 이미 정렬된 상태
        if (!isSwapped) break;
        hi--;
    }
}


// 칵테일 정렬 (Cocktail Shaker Sort)
// 버블 정렬을 양방향으로 진행하여 효율성을 높이는 방법입니다.
template<typename T>
void cocktailSort(T arr[], int n) {
    bool isSwapped = true;
    int lo = 0, hi = n - 1;

    while (isSwapped) {
        // 왼쪽에서 오른쪽으로 스캔
        isSwapped = false;
        for (int i = lo; i < hi; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        }
        // 교환이 발생하지 않았다면 이미 정렬된 상태
        if (!isSwapped) break;
 
        // 오른쪽에서 왼쪽으로 스캔
        isSwapped = false;
        hi--;
        for (int i = hi - 1; i >= lo; i--)
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        lo++;
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);

    print(arr, n);
    bubbleSort(arr, n);
    // bubbleSortOptimized(arr, n);
    // cocktailSort(arr, n);
    print(arr, n);
    return 0;
}