#pragma once

// Point Update + Range Sum Query
struct FenwickTree {
    int *tree, *arr, n;

    FenwickTree(int size) { n = size; tree = new int[n + 1]; arr = new int[n]; }
    ~FenwickTree() { delete[] tree; delete[] arr; }

    void build(int arr[]) {
        for (int i = 0; i < n; i++) update(i, arr[i]);
    }
    void update(int idx, int delta) {
        // int delta = value - arr[idx];    // update(idx, value)
        idx++;
        while (idx < n + 1) {
            tree[idx] += delta;
            idx += idx & -idx;  // 최하위 bit 더함
        }
        arr[idx] += delta;
    }
    int prefixSum(int idx) {
        idx++;
        int res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx &= idx - 1;     // 최하위 bit 제거
        }
        return res;
    }
    int query(int left, int right) {
        int res = prefixSum(right);
        if (left > 0) res -= prefixSum(left - 1);
        return res;
    }
};