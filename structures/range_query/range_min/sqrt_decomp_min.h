#pragma once
#include <cmath>

struct SqrtDecompMin {
    int *arr, n;
    int *blocks, blockSize, blockCnt;

    SqrtDecompMin(int maxSize) {
        n = maxSize;
        arr = new int[n];
        blockSize = sqrt(n);
        blockCnt = (n + blockSize - 1) / blockSize; // ceil
        blocks = new int[blockCnt];
        // initialize
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) blocks[i] = 1e6; // INF
    }
    ~SqrtDecompMin() { delete[] arr; delete[] blocks; }

    int min(int a, int b) { return (a < b) ? a : b; }
    void build(int arr[]) {
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            blocks[i / blockSize] = min(blocks[i / blockSize], arr[i]);
        }
    }
    void update(int idx, int value) {
        arr[idx] = value;
        // arr[idx] += delta;

        int blockIdx = idx / blockSize;
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);

        blocks[blockIdx] = 1e6;  // INF
        for (int i = left; i <= right; i++)
            blocks[blockIdx] = min(blocks[blockIdx], arr[i]);
    }
    int query(int left, int right) {
        int res = 1e6;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) res = min(res, arr[i]);
            return res;
        }
        for (int i = left; i < (leftBlock + 1) * blockSize; i++)
            res = min(res, arr[i]);
        for (int i = leftBlock + 1; i < rightBlock; i++)
            res = min(res, blocks[i]);
        for (int i = rightBlock * blockSize; i <= right; i++)
            res = min(res, arr[i]);
        return res;
    }
};