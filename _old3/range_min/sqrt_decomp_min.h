#pragma once
#include <cmath>

inline int min(int a, int b) { return (a < b) ? a : b; }

struct SqrtDecompMin {
    int *arr, n;
    int *blockMin, blockSize, blockCnt;

    SqrtDecompMin(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = (n + blockSize - 1) / blockSize; // ceil
        arr = new int[n];
        blockMin = new int[blockCnt];
        clear();
    }
    ~SqrtDecompMin() { delete[] arr; delete[] blockMin; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) blockMin[i] = 1e6; // INF
    }
    void build(int arr[]) {
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            blockMin[i / blockSize] = min(blockMin[i / blockSize], arr[i]);
        }
    }
    void update(int idx, int value) {
        arr[idx] = value;
        // arr[idx] += delta;

        int blockIdx = idx / blockSize;
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);

        blockMin[blockIdx] = 1e6;  // INF
        for (int i = left; i <= right; i++)
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[i]);
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
            res = min(res, blockMin[i]);
        for (int i = rightBlock * blockSize; i <= right; i++)
            res = min(res, arr[i]);
        return res;
    }
};