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

// 거의 정렬된 데이터에 대해서는 매우 효율적
// 데이터의 개수가 적을 때 자주 사용
template<typename T>
void insertionSort(T arr[], int n) {
    // 두번째 원소부터
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j;          // i번째 원소가 들어갈 자리 바로 앞
        for (j = i - 1; j >= 0 && arr[j] > temp; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);

    print(arr, n);
    insertionSort(arr, n);
    print(arr, n);

    return 0;
}
