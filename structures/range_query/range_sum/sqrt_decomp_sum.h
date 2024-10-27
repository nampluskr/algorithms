#pragma once
#include <cmath>

struct SqrtDecompSum {
    int *arr, n;
    int *blocks, blockSize, blockCnt;

    SqrtDecompSum(int maxSize) {
        n = maxSize;
        arr = new int[n];
        blockSize = sqrt(n);
        blockCnt = (n + blockSize - 1) / blockSize; // ceil
        blocks = new int[blockCnt];
        // initialize
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) blocks[i] = 0;
    }
    ~SqrtDecompSum() { delete[] arr; delete[] blocks; }

    void build(int arr[]) {
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            blocks[i / blockSize] += arr[i];
        }
    }
    void update(int idx, int value) {
        blocks[idx / blockSize] += value - arr[idx];
        arr[idx] = value;
        // blocks[idx / blockSize] += delta;
        // arr[idx] += delta;
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
        for (int i = leftBlock + 1; i < rightBlock; i++) res += blocks[i];
        for (int i = rightBlock * blockSize; i <= right; i++) res += arr[i];
        return res;
    }
};