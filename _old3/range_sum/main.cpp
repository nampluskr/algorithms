#include "segment_tree_sum.h"
#include "sqrt_decomp_sum.h"
#include "fenwick_tree.h"
#include <cstdio>

void printArray(int arr[], int low, int high) {
    printf(">> ");
    for (int i = low; i < high; i++)
        printf("%d, ", arr[i]);
    printf("%d\n", arr[high]);
}

template<typename T>
void testRangeSum(T& rng) {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("\n====================================\n");
    printArray(arr, 0, n - 1);
    rng.build(arr);
    int left = 0, right = n - 1;
    printf(">> sum [%d, %d] = %d\n", left, right, rng.query(left, right));

    int idx = 2, value = 10;
    arr[idx] = 10;
    printArray(arr, 0, n - 1);
    rng.update(idx, value);
    printf(">> sum [%d, %d] = %d\n", left, right, rng.query(left, right));
}

int main()
{
    SegmentTreeSum seg(10);
    SqrtDecompSum sqr(10);
    FenwickTree fen(10);

    testRangeSum(seg);
    testRangeSum(sqr);
    testRangeSum(fen);


    return 0;
}