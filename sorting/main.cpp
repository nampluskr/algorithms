#include "sorting.h"

#define MAX_SIZE    1'000'000   // 배열의 크기

int arr[MAX_SIZE];
int n = MAX_SIZE;               // 배열의 원소 개수
int maxNumber = 100;            // 배열의 원소 중 최대값
unsigned long long seed = 42;

int main()
{
    initArray(arr, n, maxNumber, seed);
    printArray(arr, 0, 20 - 1);

    // printf("\n[Bubble Sort (Iterative)] n = %d\n", n);

    // clock_t start = clock();
    // bubbleSort(arr, n);
    // printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    // show_result(arr, n, num);

    // init(arr, n, seed, max_num);
    // printf("\n[Bubble Sort (Recursive)] n = %d\n", n);

    // start = clock();
    // bubbleSort_recur(arr, n);
    // printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    // show_result(arr, n, num);


    return 0;
}