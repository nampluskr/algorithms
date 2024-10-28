#pragma once

struct FenwickTree {
    int *tree, *arr, n;

    FenwickTree(int max_size) {
        n = max_size;
        tree = new int[n + 1];
        arr = new int[n];
    }
    ~FenwickTree() { delete[] tree; delete[] arr; }

    void build(int arr[]) {
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            tree[i + 1] = arr[i];
        }
        for (int i = 1; i <= n; i++) {
            int idx = i + (i & -i);
            if (idx <= n) tree[idx] += tree[i];
        }
    }
    void update(int idx, int value) {
        int delta = value - arr[idx];    // update(idx, value)
        arr[idx] += delta;
        idx++;
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;  // 최하위 bit 더함
        }
    }
    int query(int left, int right) {
        int res = prefixSum(right);
        if (left > 0) res -= prefixSum(left - 1);
        return res;
    }

private:
    int prefixSum(int idx) {
        idx++;
        int res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx &= idx - 1;     // 최하위 bit 제거
        }
        return res;
    }
};