#include "segment_tree.h"
#include "sqrt_decomp.h"
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
    printf(">> min [%d, %d] = %d\n", left, right, rng.query(left, right));

    int idx = 0, delta = 10;
    arr[idx] += 10;
    printArray(arr, 0, n - 1);
    rng.update(idx, delta);
    printf(">> min [%d, %d] = %d\n", left, right, rng.query(left, right));
}

int main()
{
    int n = 10;
    auto seg = SegmentTree(n);
    auto sqr = SqrtDecomposition(n);

    testRangeSum(seg);
    testRangeSum(sqr);

    return 0;
}