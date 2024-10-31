#pragma once

#include "math_func.h"

// Without lazy propagation
struct SqrtDecompMinLazyV1 {
    int* arr, n;
    int* blockMin, blockSize, blockCnt;
    int* lazy;
    const int defaultValue = 1e6;   // INF

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

    void updateRange(int left, int right, int delta) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                arr[i] += delta;
            updateBlock(leftBlock);
        } else {
            for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
                arr[i] += delta;
            updateBlock(leftBlock);
            for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
                lazy[i] += delta;
            for (int i = rightBlock * blockSize; i <= right; i++)
                arr[i] += delta;
            updateBlock(rightBlock);
        }
    }

    int queryPoint(int idx) { return arr[idx] + lazy[idx / blockSize];}

    int queryRange(int left, int right) {
        int res = defaultValue;     // INF
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++)
                res = min(res, arr[i] + lazy[leftBlock]);
        } else {
            for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
                res = min(res, arr[i] + lazy[leftBlock]);
            for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
                res = min(res, blockMin[i] + lazy[i]);
            for (int i = rightBlock * blockSize; i <= right; i++)
                res = min(res, arr[i] + lazy[rightBlock]);
        }
        return res;
    }

private:
    void updateBlock(int blockIdx) {
        blockMin[blockIdx] = defaultValue;
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        for (int i = left; i <= right; i++)
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[i] + lazy[blockIdx]);
    }
};