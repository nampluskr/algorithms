#pragma once

#include "math_func.h"

struct SqrtDecompMin {
    int* arr, n;
    int* blockMin, blockSize, blockCnt;
    const int defaultValue = 1e6;   // INF

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
        arr[idx] += delta;
        updateBlock(idx / blockSize);
    }

    int queryRange(int left, int right) {
        int res = defaultValue;     // INF
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res = min(res, arr[i]);
        } else {
            for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
                res = min(res, arr[i]);
            for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
                res += blockMin[i];
            for (int i = rightBlock * blockSize; i <= right; i++)
                res = min(res, arr[i]);
        }
        return res;
    }

private:
    void updateBlock(int blockIdx) {
        blockMin[blockIdx] = defaultValue;
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        for (int i = left; i <= right; i++)
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[i]);
    }
};