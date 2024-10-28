### Sqrt Decomposition for Range Sumg Query with Lazy Propagation

```cpp
#pragma once

#include <vector>
#include <cmath>
using namespace std;

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

struct SqrtDecompSumLazy {
    int* arr, n;
    int* blockSum, blockSize, blockCnt;
    int* lazy;

    SqrtDecompSumLazy(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = (n + blockSize - 1) / blockSize;

        arr = new int[n];
        blockSum = new int[blockCnt];
        lazy = new int[blockCnt];
        clear();
    }
    ~SqrtDecompSumLazy() { delete[] arr; delete[] blockSum; delete[] lazy; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) { blockSum[i] = lazy[i] = 0; }
    }
    void build(int _arr[]) {
        for (int i = 0; i < n; i++) {
            arr[i] = _arr[i];
            blockSum[i / blockSize] += _arr[i];
        }
    }
    void updatePoint(int idx, int delta) { 
        arr[idx] += delta;
        blockSum[idx / blockSize] += delta;
    }
    void updateRange(int left, int right, int delta) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) arr[i] += delta;
            propagate(leftBlock);    
            return;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++) arr[i] += delta;
        propagate(leftBlock);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++) lazy[i] += delta;
        for (int i = rightBlock * blockSize; i <= right; i++) arr[i] += delta;
        propagate(rightBlock);
    }
    int queryPoint(int idx) { return arr[idx] + lazy[idx / blockSize]; }
    int queryRange(int left, int right) {
        int res = 0;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) res += queryPoint(i);
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
private:
    void propagate(int blockIdx) {
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        blockSum[blockIdx] = 0;
        for (int i = left; i <= right; i++)
            blockSum[blockIdx] += queryPoint(i);
    }
    // void propagate(int blockIdx) {
    //     if (lazy[blockIdx] == 0) return;
    //     int left = blockIdx * blockSize;
    //     int right = min((blockIdx + 1) * blockSize - 1, n - 1);
    //     blockSum[blockIdx] = 0;
    //     for (int i = left; i <= right; i++) {
    //         arr[i] += lazy[blockIdx];
    //         // blockSum[blockIdx] += arr[i];
    //     }
    //     blockSum[blockIdx] += lazy[blockIdx] * (right - left + 1);
    //     lazy[blockIdx] = 0;
    // }
};
```

### Sqrt Decomposition for Range Min Query with Lazy Propagation

```cpp
#pragma once

#include <cmath>

const int INF = 1e6;
inline int min(int a, int b) { return (a < b) ? a : b; }

struct SqrtDecompMinLazy {
    int* arr, n;
    int* blockMin, blockSize, blockCnt;
    int* lazy;

    SqrtDecompMinLazy(int maxSize) {
        n = maxSize;
        blockSize = sqrt(n);
        blockCnt = (n + blockSize - 1) / blockSize;

        arr = new int[n];
        blockMin = new int[blockCnt];
        lazy = new int[blockCnt];
        clear();
    }
    ~SqrtDecompMinLazy() { delete[] arr; delete[] blockMin; delete[] lazy; }

    void clear() {
        for (int i = 0; i < n; i++) arr[i] = 0;
        for (int i = 0; i < blockCnt; i++) { blockMin[i] = INF; lazy[i] = 0; }
    }
    void build(int _arr[]) {
        for (int i = 0; i < n; i++) {
            arr[i] = _arr[i];
            blockMin[i / blockSize] = min(blockMin[i / blockSize], arr[i]);
        }
    }
    void updatePoint(int idx, int delta) {
        arr[idx] += delta;
        propagate(idx / blockSize);
    }
    void updateRange(int left, int right, int delta) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) arr[i] += delta;
            propagate(leftBlock);
            return;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++) arr[i] += delta;
        propagate(leftBlock);
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++) lazy[i] += delta;
        for (int i = rightBlock * blockSize; i <= right; i++) arr[i] += delta;
        propagate(rightBlock);
    }
    int queryPoint(int idx) { return arr[idx] + lazy[idx / blockSize]; }
    int queryRange(int left, int right) {
        int res = INF;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;
 
        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) res = min(res, queryPoint(i));
            return res;
        }
        for (int i = left; i <= (leftBlock + 1) * blockSize - 1; i++)
            res = min(res, queryPoint(i));
        for (int i = leftBlock + 1; i <= rightBlock - 1; i++)
            res = min(res, blockMin[i] + lazy[i] * blockSize);
        for (int i = rightBlock * blockSize; i <= right; i++)
            res = min(res, queryPoint(i));
        return res;
    }

private:
    // void propagate(int blockIdx) {
    //     int left = blockIdx * blockSize;
    //     int right = min((blockIdx + 1) * blockSize - 1, n - 1);
    //     blockMin[blockIdx] = INF;
    //     for (int i = left; i <= right; i++)
    //         blockMin[blockIdx] = min(blockMin[blockIdx], queryPoint(i));
    // }
    void propagate(int blockIdx) {
        if (lazy[blockIdx] == 0) return;
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);
        blockMin[blockIdx] = INF;
        for (int i = left; i <= right; i++) {
            arr[i] += lazy[blockIdx];
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[i]);
        }
        lazy[blockIdx] = 0;
    }
};
```
