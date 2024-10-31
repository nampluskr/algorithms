#pragma once

#include "math_func.h"

struct SqrtDecompSumLazy {
    int* arr, n;
    int* blockSum, blockSize, blockCnt;
    int* lazy;
    const int defaultValue = 0;

    SqrtDecompSumLazy(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = ceil(n, blockSize);
        arr = new int[n];
        blockSum = new int[blockCnt];
        lazy = new int[blockCnt];
        clear();
    }
    ~SqrtDecompSumLazy() { delete[] arr; delete[] blockSum; delete[] lazy; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) blockSum[i] = defaultValue;
    }

    void build(int _arr[]) {
        for (int i = 0; i < n; i++) {
            arr[i] += _arr[i];
            blockSum[i / blockSize] += _arr[i];
        }
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
        } else {
            for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
                res += arr[i];
            for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
                res += blockSum[i];
            for (int i = rightBlock * blockSize; i <= right; i++)
                res += arr[i];
        }
        return res;
    }
};