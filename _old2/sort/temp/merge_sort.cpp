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

#if 0
void merge(int arr1[], int n1, int arr2[], int n2, int aux[]) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) aux[k++] = arr1[i++];
        else aux[k++] = arr2[j++];
    }
    while (i < n1) { aux[k++] = arr1[i++]; }
    while (j < n2) { aux[k++] = arr2[j++]; }
}

void mergeSort(int arr[], int lo, int hi) {
    if (lo >= hi) return; // 요소가 하나 이하이면 정렬할 필요 없음

    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid + 1, hi);

    int aux[hi - lo + 1];
    merge(arr + lo, mid - lo + 1, arr + mid + 1, hi - mid, aux);
    for (int i = lo, j = 0; i <= hi; i++, j++) arr[i] = aux[j];
}
#else
// [Gemini]
void merge(int arr[], int lo, int mid, int hi) {
    int i, j, k;
    int n1 = mid - lo + 1;
    int n2 = hi - mid;
    int L[n1], R[n2];   // create temp arrays

    // copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++) L[i] = arr[lo + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;      // Initial index of first sub-array
    j = 0;      // Initial index of second sub-array
    k = lo;     // Initial index of merged sub-array
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];    // Copy the remaining elements of L[]
    while (j < n2) arr[k++] = R[j++];    // Copy the remaining elements of R[]
}

template<typename T>
void mergeSort(T arr[], int lo, int hi) {
    if (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        mergeSort(arr, lo, mid);
        mergeSort(arr, mid + 1, hi);
        merge(arr, lo, mid, hi);
    }
}
#endif

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    print(arr, n);
    mergeSort(arr, 0, n - 1);
    print(arr, n);

    return 0;
}
