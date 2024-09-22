#pragma once

// [Immutable] build O(N) + Range Sum Query O(1)
struct PrefixSum{
    int *table, *arr, n;

    PrefixSum(int max_size) {
        n = max_size;
        table = new int[max_size + 1];
        arr = new int[max_size];
    }
    ~PrefixSum() { delete[] table; delete[] arr; }

    void build(int arr[], int size) {
        n = size;
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
            table[i + 1] = table[i] + arr[i];
        }
    }
    void update(int idx, int value) {
        arr[idx] = value;   // arr[idx] += delta;
        build(arr, n);
    }
    int query(int left, int right) {
        return table[right + 1] - table[left];
    }
};