### math_func.h

```cpp
inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }
inline int ceil(int a, int b) { return (a + b - 1) / b; }

int sqrt(int n) {
    bool decreased = false;
    int x = n, nx = (x + n / x) >> 1;
    while (true) {
        if (x == nx || (x < nx && decreased)) break;
        decreased = x > nx;
        x = nx, nx = (x + n / x) >> 1;
    }
    return x;
}
```

### sqrt_decomp_sum.h

```cpp
#pragma once
#include "math_func.h"

struct SqrtDecompSum {
    int* arr, n;
    int* blockSum, blockSize, blockCnt;
    const int defaultValue = 0;

    SqrtDecompSum(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = ceil(n, blockSize);
        arr = new int[n];
        blockSum = new int[blockCnt];
        clear();
    }
    ~SqrtDecompSum() { delete[] arr; delete[] blockSum; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) blockSum[i] = defaultValue;
    }

    void build(int _arr[]) {
        for (int i = 0; i < n; i++) arr[i] += _arr[i];
        for (int i = 0; i < blockCnt; i++) updateBlock(i);
    }

    void updatePoint(int idx, int delta) {
        arr[idx] += delta;
        blockSum[idx / idx] += delta;
    }

    int queryRange(int left, int right) {
        int res = defaultValue;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res += arr[i];
            return res;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            res += arr[i];
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            res += blockSum[i];
        for (int i = rightBlock * blockSize; i <= right; i++)
            res += arr[i];
        return res;
    }

private:
    void updateBlock(int blockIdx) {
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        blockSum[blockIdx] = defaultValue;
        for (int i = left; i <= right; i++)
            blockSum[blockIdx] += arr[i];
    }
};

// range update without lazy propagation
struct SqrtDecompSumLazyV1 {
    int* arr, n;
    int* blockSum, blockSize, blockCnt;
    int* lazy;
    const int defaultValue = 0;

    SqrtDecompSumLazyV1(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = ceil(n, blockSize);
        arr = new int[n];
        blockSum = new int[blockCnt];
        lazy = new int[blockCnt];
        clear();
    }
    ~SqrtDecompSumLazyV1() { delete[] arr; delete[] blockSum; delete[] lazy; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) { blockSum[i] = defaultValue; lazy[i] = 0; }
    }

    void build(int _arr[]) {
        for (int i = 0; i < n; i++) {
            arr[i] += _arr[i];
            blockSum[i / blockSize] += _arr[i];
        }
    }

    void updatePoint(int idx, int delta) {
        arr[idx] += delta;
        blockSum[idx / idx] += delta;   // update block
    }

    void updateRange(int left, int right, int delta) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                updatePoint(i, delta);
            return;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            updatePoint(i, delta);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            lazy[i] += delta;
        for (int i = rightBlock * blockSize; i <= right; i++)
            updatePoint(i, delta);
    }

    int queryPoint(int idx) { return arr[idx] + lazy[idx / blockSize];}

    int queryRange(int left, int right) {
        int res = defaultValue;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res += queryPoint(i);
            return res;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            res += queryPoint(i);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            res += blockSum[i] + lazy[i] * blockSize;
        for (int i = rightBlock * blockSize; i <= right; i++)
            res += queryPoint(i);
        return res;
    }
};

// range update with lazy propagation
struct SqrtDecompSumLazyV2 {
    int* arr, n;
    int* blockSum, blockSize, blockCnt;
    int* lazy;
    const int defaultValue = 0;

    SqrtDecompSumLazyV2(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = ceil(n, blockSize);
        arr = new int[n];
        blockSum = new int[blockCnt];
        lazy = new int[blockCnt];
        clear();
    }
    ~SqrtDecompSumLazyV2() { delete[] arr; delete[] blockSum; delete[] lazy; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) { blockSum[i] = defaultValue; lazy[i] = 0; }
    }

    void build(int _arr[]) {
        for (int i = 0; i < n; i++) {
            arr[i] += _arr[i];
            blockSum[i / blockSize] += _arr[i]; // update block
        }
    }

    void updatePoint(int idx, int delta) {
        arr[idx] += delta;
        blockSum[idx / idx] += delta;   // update block
    }

    void updateRange(int left, int right, int delta) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        propagate(leftBlock);
        if (leftBlock != rightBlock) propagate(rightBlock);

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                updatePoint(i, delta);
            return;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            updatePoint(i, delta);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            lazy[i] += delta;
        for (int i = rightBlock * blockSize; i <= right; i++)
            updatePoint(i, delta);
    }

    int queryPoint(int idx) { return arr[idx] + lazy[idx / blockSize];}

    int queryRange(int left, int right) {
        int res = defaultValue;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        propagate(leftBlock);
        if (leftBlock != rightBlock) propagate(rightBlock);

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res += arr[i];  // lazy[leftBlock] == 0
            return res;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            res += arr[i];      // lazy[leftBlock] == 0
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            res += blockSum[i] + lazy[i] * blockSize;
        for (int i = rightBlock * blockSize; i <= right; i++)
            res += arr[i];      // lazy[rightBlock] == 0
        return res;
    }

private:
    void propagate(int blockIdx) {
        if (lazy[blockIdx] == 0) return;

        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        for (int i = left; i <= right; i++) arr[i] += lazy[blockIdx];
        blockSum[blockIdx] += lazy[blockIdx] * (right - left + 1);
        lazy[blockIdx] = 0;
    }
};
```

### sqrt_decomp_min.h

```cpp
#pragma once
#include "math_func.h"

struct SqrtDecompMin {
    int* arr, n;
    int* blockMin, blockSize, blockCnt;
    const int defaultValue = 1e6;

    SqrtDecompMin(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = ceil(n, blockSize);
        arr = new int[n];
        blockMin = new int[blockCnt];
        clear();
    }
    ~SqrtDecompMin() { delete[] arr; delete[] blockMin; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) blockMin[i] = defaultValue;
    }

    void build(int _arr[]) {
        for (int i = 0; i < n; i++) arr[i] += _arr[i];
        for (int i = 0; i < blockCnt; i++) updateBlock(i);
    }

    void updatePoint(int idx, int delta) {
        int blockIdx = idx / blockSize;
        if (blockMin[blockIdx] != arr[idx]) {
            arr[idx] += delta;
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[idx]);
        } else {
            arr[idx] += delta;
            updateBlock(blockIdx);
        }
    }

    int queryRange(int left, int right) {
        int res = defaultValue;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res = min(res, arr[i]);
            return res;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            res = min(res, arr[i]);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            res = min(res, blockMin[i]);
        for (int i = rightBlock * blockSize; i <= right; i++)
            res = min(res, arr[i]);
        return res;
    }

private:
    void updateBlock(int blockIdx) {
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        blockMin[blockIdx] = defaultValue;
        for (int i = left; i <= right; i++)
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[i]);
    }
};

// range update without lazy propagation
struct SqrtDecompMinLazyV1 {
    int* arr, n;
    int* blockMin, blockSize, blockCnt;
    int* lazy;
    const int defaultValue = 1e6;

    SqrtDecompMinLazyV1(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = ceil(n, blockSize);
        arr = new int[n];
        blockMin = new int[blockCnt];
        lazy = new int[blockCnt];
        clear();
    }
    ~SqrtDecompMinLazyV1() { delete[] arr; delete[] blockMin; delete[] lazy; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) { blockMin[i] = defaultValue; lazy[i] = 0; }
    }

    void build(int _arr[]) {
        for (int i = 0; i < n; i++) arr[i] += _arr[i];
        for (int i = 0; i < blockCnt; i++) updateBlock(i);
    }

    void updatePoint(int idx, int delta) {
        int blockIdx = idx / blockSize;
        if (blockMin[blockIdx] != arr[idx]) {
            arr[idx] += delta;
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[idx]) + lazy[blockIdx];
        } else {
            arr[idx] += delta;
            updateBlock(blockIdx);
        }
    }

    void updateRange(int left, int right, int delta) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                arr[i] += delta;
            updateBlock(leftBlock);
            return;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            arr[i] += delta;
        updateBlock(leftBlock);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            lazy[i] += delta;                                       // *** lazy
        for (int i = rightBlock * blockSize; i <= right; i++)
            arr[i] += delta;
        updateBlock(rightBlock);
    }

    int queryPoint(int idx) { return arr[idx] + lazy[idx / blockSize];}

    int queryRange(int left, int right) {
        int res = defaultValue;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res = min(res, queryPoint(i));
            return res;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            res = min(res, queryPoint(i));
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            res = min(res, blockMin[i] + lazy[i]);                  // *** lazy
        for (int i = rightBlock * blockSize; i <= right; i++)
            res = min(res, queryPoint(i));
        return res;
    }

private:
    // arr[i] updated and lazy(blockIdx) != 0
    void updateBlock(int blockIdx) {
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        blockMin[blockIdx] = defaultValue;
        for (int i = left; i <= right; i++)
            blockMin[blockIdx] = min(blockMin[blockIdx], queryPoint(i));
    }
};

// range update with lazy propagation
struct SqrtDecompMinLazyV2 {
    int* arr, n;
    int* blockMin, blockSize, blockCnt;
    int* lazy;
    const int defaultValue = 1e6;

    SqrtDecompMinLazyV2(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = ceil(n, blockSize);
        arr = new int[n];
        blockMin = new int[blockCnt];
        lazy = new int[blockCnt];
        clear();
    }
    ~SqrtDecompMinLazyV2() { delete[] arr; delete[] blockMin; delete[] lazy; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) { blockMin[i] = defaultValue; lazy[i] = 0; }
    }

    void build(int _arr[]) {
        for (int i = 0; i < n; i++) arr[i] += _arr[i];
        for (int i = 0; i < blockCnt; i++) updateBlock(i);
    }

    void updatePoint(int idx, int delta) {
        propagate(idx / blockSize);
        arr[idx] += delta;
        updateBlock(idx / blockSize);
    }

    void updateRange(int left, int right, int delta) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        propagate(leftBlock);
        if (leftBlock != rightBlock) propagate(rightBlock);

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                arr[i] += delta;
            updateBlock(leftBlock);
            return;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            arr[i] += delta;
        updateBlock(leftBlock);

        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            lazy[i] += delta;

        for (int i = rightBlock * blockSize; i <= right; i++)
            arr[i] += delta;
        updateBlock(rightBlock);
    }

    int queryPoint(int idx) { return arr[idx] + lazy[idx / blockSize];}

    int queryRange(int left, int right) {
        int res = defaultValue;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        propagate(leftBlock);
        if (leftBlock != rightBlock) propagate(rightBlock);

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res = min(res, arr[i]);     // lazy[leftBlock] == 0
            return res;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            res = min(res, arr[i]);         // lazy[leftBlock] == 0
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            res = min(res, blockMin[i] + lazy[i]);
        for (int i = rightBlock * blockSize; i <= right; i++)
            res = min(res, arr[i]);         // lazy[rightBlock] == 0
        return res;
    }

private:
    // arr[i] updated and lazy(blockIdx) == 0
    void updateBlock(int blockIdx) {
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        blockMin[blockIdx] = defaultValue;
        for (int i = left; i <= right; i++)
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[i]);
    }
    void propagate(int blockIdx) {
        if (lazy[blockIdx] == 0) return;

        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        for (int i = left; i <= right; i++) arr[i] += lazy[blockIdx];
        blockMin[blockIdx] += lazy[blockIdx];
        lazy[blockIdx] = 0;
    }
};
```

### main.cpp

```cpp
#include "sqrt_decomp_min.h"
#include "sqrt_decomp_sum.h"
#include <cstdio>

template<typename T>
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
    SqrtDecompSumLazyV1 sqr2(10);
    SqrtDecompSumLazyV2 sqr3(10);

    SqrtDecompMin sqr4(10);
    SqrtDecompMinLazyV1 sqr5(10);
    SqrtDecompMinLazyV2 sqr6(10);

    testSqrtDecomp(sqr1);
    testSqrtDecomp(sqr2);
    testSqrtDecomp(sqr3);
    testSqrtDecomp(sqr4);
    testSqrtDecomp(sqr5);
    testSqrtDecomp(sqr6);

    return 0;
}
```
