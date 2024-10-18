#if 0
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

int min(int a, int b) { return (a < b)? a: b; }
int max(int a, int b) { return (a < b)? b: a; }

// int MED3(int arr[], int lo, int mid, int hi) {
//     return max(min(arr[lo], arr[mid]), min(max(arr[lo], arr[mid]), arr[hi]));
// }

int MED3(int arr[], int lo, int mid, int hi) {
    int a = arr[lo], b = arr[mid], c = arr[hi];
    if (a < b) {
        if (b < c) return b;
        else return a < c ? c : a;
    } else {
        if (b > c) return b;
        else return a > c ? c : a;
    }
}

// 5개 이하의 요소를 Insertion Sort로 정렬하고 중앙값 반환
int findMedianOfFive(int arr[], int lo, int hi) {
    for (int i = lo + 1; i <= hi; i++) {
        int temp = arr[i];
        int j = i - 1;
        for (j = i - 1; j >= lo && arr[j] > temp; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
    return arr[lo + 2];
}

// Median-of-Medians 함수
// int medianOfMedians(int arr[], int lo, int hi) {
//     int n = hi - lo + 1;

//     // 5개씩 그룹으로 나누고, 각 그룹의 중앙값을 찾아 새로운 배열에 저장
//     int numGroups = (n + 4) / 5;
//     int medians[numGroups];
//     for (int i = 0; i < numGroups; i++) {
//         int groupLow = lo + i * 5;
//         int groupHigh = min(lo + (i + 1) * 5 - 1, hi);
//         medians[i] = findMedianOfFive(arr, groupLow, groupHigh);
//     }
//     // 중앙값의 중앙값을 재귀적으로 찾음
//     return medianOfMedians(medians, 0, numGroups - 1);
// }

// 중앙값의 중앙값을 구하는 함수
int medianOfMedians(int arr[], int left, int right) {
    int n = right - left + 1;

    // 작은 그룹으로 나누기 위한 기준
    const int groupSize = 5;

    // 작은 그룹의 중앙값을 저장할 임시 배열
    int* medians = new int[n / groupSize + 1];
    int medianIndex = 0;

    // 각 그룹의 중앙값 구하기
    for (int i = left; i <= right; i += groupSize) {
        int end = min(i + groupSize - 1, right);
        sort(arr + i, arr + end + 1); // std::sort 사용
        medians[medianIndex++] = arr[(i + end) / 2];
    }

    // 중앙값의 중앙값 구하기 (재귀적으로 호출)
    int medianOfMedians = select(medians, 0, medianIndex - 1, medianIndex / 2);

    // 동적 할당된 메모리 해제
    delete[] medians;

    return medianOfMedians;
}



// [재귀 호출 범위] 분할된 후, 피벗을 포함한 오른쪽 부분만 재귀적으로 정렬합니다. 왼쪽 부분은 이미 정렬된 상태이기 때문입니다.
// 한 개의 포인터만 사용하여 파티션을 수행하기 때문에 코드가 간단합니다.
// 구현이 간단하며, 대부분의 경우 무난한 성능을 보입니다. 모든 요소가 동일한 값일 경우 비효율적일 수 있습니다.
int lomutoPartition(int arr[], int lo, int hi) {
    int pivot = arr[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[++i], arr[hi]);  // 피벗을 최종 위치로 이동
    return i;
}

int choosePivot(int arr[], int lo, int hi) {
    int n = hi - lo + 1;
    int mid = (lo + hi) / 2;
    if (n > 7) {
        if (n > 40) {
            int d = n / 8;
            lo = MED3(arr, lo, lo + d, lo + 2*d);
            mid = MED3(arr, mid - d, mid, mid + d);
            hi = MED3(arr, hi - 2*d, hi - d, hi);
        }
        mid = MED3(arr, lo, mid, hi);
    }
    return mid;
}

// [재귀 호출 범위] 분할된 후, 피벗의 위치를 기준으로 왼쪽 부분과 오른쪽 부분을 재귀적으로 정렬합니다.
// 두 개의 포인터를 사용하여 파티션을 수행하기 때문에 코드가 약간 더 복잡합니다.
// 일반적으로 더 효율적이며, 모든 요소가 동일한 값일 경우에도 잘 작동합니다. 코드가 약간 더 복잡합니다.
int hoarePartition(int arr[], int lo, int hi) {
    // pivot을 첫번째 또는 마지막 값을 선택한다면 반드시 추가적인 범위 검사 코드 필요
    // int pivot = arr[(lo + hi) / 2];
    // int pivot = medianOfMedians(arr, lo, hi); // >> Error!
    // int pivot = MED3(arr, lo, (lo + hi) / 2, hi);
    int pivot = arr[choosePivot(arr, lo, hi)];
    int i = lo - 1, j = hi + 1;

    while (true) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);

        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    return j;
}

// int hoarePartition(int arr[], int lo, int hi) {
//     int pivot = arr[(lo + hi) / 2];
//     int i = lo, j = hi;

//     while (i <= j) {
//         while (arr[i] < pivot) i++;
//         while (arr[j] > pivot) j--;

//         if (i < j) swap(arr[i++], arr[j--]);
//         else i++;
//     }
//     return j;
// }

template<typename T>
void quickSort(T arr[], int lo, int hi) {
    if (lo < hi) {
        if (1) {
            int pivotIndex = hoarePartition(arr, lo, hi);
            quickSort(arr, lo, pivotIndex);
            quickSort(arr, pivotIndex + 1, hi);
        } else {
            int pivotIndex = lomutoPartition(arr, lo, hi);
            quickSort(arr, lo, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, hi);
        }
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    print(arr, n);
    quickSort(arr, 0, n - 1);
    print(arr, n);

    return 0;
}
#endif