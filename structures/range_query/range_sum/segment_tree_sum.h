#pragma once

struct SegmentTreeSum {
    int *tree, n;
    int defaultValue = 0;

    SegmentTreeSum(int maxSize) { n = maxSize; tree = new int[4 * n]; }
    ~SegmentTreeSum() { delete[] tree; }

    void build(int arr[]) { build(arr, 1, 0, n - 1); }
    void update(int idx, int value) { update(idx, value, 1, 0, n - 1); }
    int query(int left, int right) { return query(left, right, 1, 0, n - 1); }

private:
    int merge(int leftValue, int rightValue) { return leftValue + rightValue; }
    int build(int arr[], int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];

        int mid = start + (end - start) / 2;
        int leftValue = build(arr, node * 2, start, mid);
        int rightValue = build(arr, node * 2 + 1, mid + 1, end);
        return tree[node] = merge(leftValue, rightValue);
    }
    int update(int idx, int value, int node, int start, int end) {
        if (idx < start || end < idx) return tree[node];
        // if (start == end) return tree[node] += delta;
        if (start == end) return tree[node] = value; // update(idx, value, ...)

        int mid = start + (end - start) / 2;
        int leftValue = update(idx, value, node * 2, start, mid );
        int rightValue = update(idx, value, node * 2 + 1, mid + 1, end);
        return tree[node] = merge(leftValue, rightValue);
    }
    int query(int left, int right, int node, int start, int end) {
        if (right < start || end < left) return defaultValue;
        if (left <= start && end <= right) return tree[node];

        int mid = start + (end - start) / 2;
        int leftValue = query(left, right, node * 2, start, mid);
        int rightValue = query(left, right, node * 2 + 1, mid + 1, end);
        return merge(leftValue, rightValue);
    }
};