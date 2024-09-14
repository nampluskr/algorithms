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

// 일정한 간격을 두고 요소들을 비교하며 정렬, 간격을 점차 줄여나감
// 간격 계산 방법에 따라 성능이 달라질 수 있으며, 최악의 경우 시간 복잡도는 삽입 정렬과 동일
// [Gemini]
// template<typename T>
// void shellSort(T arr[], int n) {
//     for (int gap = n/2; gap > 0; gap /= 2) {
//         for (int i = gap; i < n; i += gap) {
//             int temp = arr[i];
//             int j;
//             for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
//                 arr[j] = arr[j-gap];
//             }
//             arr[j] = temp;
//         }
//     }
// }

template<typename T>
void shellSort(T arr[], int n) {
    int h = 1;
    while (h < n / 3) h = h * 3 + 1;    // 1, 4, 13, 40, 121, 363, 1093, ...

    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i - h; j >= 0 && arr[j] > temp; j -= h)
                arr[j + h] = arr[j];
            arr[j + h] = temp;
        }
        h /= 3;
    }
}


int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);

    print(arr, n);
    shellSort(arr, n);
    print(arr, n);

    return 0;
}
