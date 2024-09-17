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

template<typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        // 최소값과 현재 위치의 값을 교환
        swap(arr[minIndex], arr[i]);
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);

    print(arr, n);
    selectionSort(arr, n);

    print(arr, n);
    return 0;
}