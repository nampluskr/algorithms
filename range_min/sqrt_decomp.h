#pragma once

#include <cmath>

// Point Update + Range Sum Query
struct SqrtDecomposition {
    int *blocks, blockSize, blockCnt;
    int *arr, n;

    SqrtDecomposition(int size) {
        n = size;
        blockSize = sqrt(n);
        blockCnt = (n + blockSize - 1) / blockSize; // ceil
        blocks = new int[blockCnt]; arr = new int[n];
    }
    ~SqrtDecomposition() { delete[] arr; delete[] blocks; }

    inline int min(int a, int b) { return (a < b) ? a : b; }
    void build(int arr[]) {
        for (int i = 0; i < blockCnt; i++) blocks[i] = 1e6;
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            blocks[i / blockSize] = min(blocks[i / blockSize], arr[i]);
        }
    }
    void update(int idx, int delta) {
        // int delta = value - arr[idx];    // update(idx, value)
        arr[idx] += delta;

        int bIdx = idx / blockSize;
        int left = bIdx * blockSize;
        int right = min((bIdx + 1) * blockSize - 1, blockCnt - 1);

        blocks[bIdx] = 1e6;
        for (int i = left; i <= right; i++)
            blocks[bIdx] = min(blocks[bIdx], arr[i]);
    }
    int query(int left, int right) {
        int res = 1e6;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) res = min(res, arr[i]);
            return res;
        }
        for (int i = left; i < (leftBlock + 1) * blockSize; i++) res = min(res, arr[i]);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++) res = min(res, blocks[i]);
        for (int i = rightBlock * blockSize; i <= right; i++) res = min(res, arr[i]);
        return res;
    }
};