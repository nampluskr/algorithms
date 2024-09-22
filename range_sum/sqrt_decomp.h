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

    void build(int arr[]) {
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            blocks[i / blockSize] += arr[i];
        }
    }
    void update(int idx, int delta) {
        // int delta = value - arr[idx];    // update(idx, value)
        blocks[idx / blockSize] += delta;
        arr[idx] += delta;
    }
    int query(int left, int right) {
        int res = 0;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) res += arr[i];
            return res;
        }
        for (int i = left; i < (leftBlock + 1) * blockSize; i++) res += arr[i];
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++) res += blocks[i];
        for (int i = rightBlock * blockSize; i <= right; i++) res += arr[i];
        return res;
    }
};