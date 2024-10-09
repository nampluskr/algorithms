#pragma once

int log2(int n) {
    int res = 0;
    while (n >>= 1) res++;
    return res;
}

// [Immutable] build O(N log N) + Range Min Query O(1)
struct SparseTable {
    int **table, *arr, n;

    SparseTable(int max_size) {
        n = max_size;
        arr = new int[n];
        int max_log = log2(n) + 1;
        table = new int*[n];
        for (int i = 0; i < n; i++) table[i] = new int[max_log];
    }
    ~SparseTable() {
        delete[] arr;
        for (int i = 0; i < n; i++) delete[] table[i];
        delete[] table;
    }

    inline int min(int a, int b) { return (a < b) ? a : b; }
    void build(int arr[], int size) {
        n = size;
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            table[i][0] = arr[i];
        }
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }
    void update(int idx, int value) {
        arr[idx] = value;
        build(arr, n);
    }
    int query(int left, int right) {
        int k = log2(right - left + 1);
        return min(table[left][k], table[right + 1 - (1 << k)][k]);
    }
};