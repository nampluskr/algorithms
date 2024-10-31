#include <cstdio>
#include "sqrt_decomp_min.h"
#include "sqrt_decomp_sum.h"

template <typename T>
void testSqrtDecomp(T& sqr) {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int left = 0, right = n - 1, res;

    printf("\n");
    sqr.build(arr);

    res = sqr.queryRange(left, right);
    printf(">> Query[%d:%d] = %d\n", left, right, res);

    sqr.updatePoint(0, 10);          // arr[0] = 3
    res = sqr.queryRange(left, right);
    printf(">> Query[%d:%d] = %d\n", left, right, res);

    left = right = 0;
    res = sqr.queryRange(left, right);
    printf(">> Query[%d:%d] = %d\n", left, right, res);   // arr[0] = 3
}

int main()
{
    SqrtDecompSum sqr1(10);
    SqrtDecompMin sqr2(10);

    testSqrtDecomp(sqr1);
    testSqrtDecomp(sqr2);

    return 0;
}