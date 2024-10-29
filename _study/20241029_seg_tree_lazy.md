### Segment Tree Sum

```cpp
#pragma once

inline int sum(int a, int b) { return a + b; }

struct SegmentTreeSum {
    int* tree, n;
    const int defaultValue = 0;

    SegmentTreeSum(int maxSize) { n = maxSize; tree = new int[4 * n]; }
    ~SegmentTreeSum() { delete[] tree; }

    int build(int arr[], int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];

        int mid = start + (end - start) / 2;
        int leftValue = build(arr, 2 * node, start, mid);
        int rightValue = build(arr, 2 * node + 1, mid + 1, end);
        return tree[node] = sum(leftValue, rightValue);
    }
    int updatePoint(int idx, int delta, int node, int start, int end) {
        if (idx < start || end < idx) return tree[node];
        if (start == end) return tree[node] += delta;

        int mid = start + (end - start) / 2;
        int leftValue = updatePoint(idx, delta, 2* node, start, mid);
        int rightValue = updatePoint(idx, delta, 2* node + 1, mid + 1, end);
        return tree[node] = sum(leftValue, rightValue);
    }
    int queryRange(int left, int right, int node, int start, int end) { 
        if (right < start || end < left) return defaultValue;
        if (left <= start && end <= right) return tree[node];

        int mid = start + (end - start) / 2;
        int leftValue = queryRange(left, right, 2* node, start, mid);
        int rightValue = queryRange(left, right, 2* node + 1, mid + 1, end);
        return sum(leftValue, rightValue);
    }
};

struct SegmentTreeSumLazy {
    int* tree, * lazy, n;
    const int defaultValue = 0;

    SegmentTreeSumLazy(int maxSize) { 
        n = maxSize;
        tree = new int[4 * n];
        lazy = new int[4 * n];
    }
    ~SegmentTreeSumLazy() { delete[] tree; delete[] lazy; }

    int build(int arr[], int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];

        int mid = start + (end - start) / 2;
        int leftValue = build(arr, 2 * node, start, mid);
        int rightValue = build(arr, 2 * node + 1, mid + 1, end);
        return tree[node] = sum(leftValue, rightValue);
    }
    int updatePoint(int idx, int delta, int node, int start, int end) {
        if (idx < start || end < idx) return tree[node];
        if (start == end) return tree[node] += delta;

        int mid = start + (end - start) / 2;
        int leftValue = updatePoint(idx, delta, 2* node, start, mid);
        int rightValue = updatePoint(idx, delta, 2* node + 1, mid + 1, end);
        return tree[node] = sum(leftValue, rightValue);
    }
    int updateRange(int left, int right, int delta, int node, int start, int end) {
        propagate(node, start, end);
        if (right < start || end < left) return tree[node];
        if (left <= start && end <= right) {
            if (start != end) {
                lazy[2 * node] += delta;
                lazy[2 * node + 1] += delta;
            }
            return tree[node] += delta * (end - start + 1); // sum
        }
        int mid = start + (end - start) / 2;
        int leftValue = updateRange(left, right, delta, 2* node, start, mid);
        int rightValue = updateRange(left, right, delta, 2* node + 1, mid + 1, end);
        return tree[node] = sum(leftValue, rightValue);

    }
    int queryRange(int left, int right, int node, int start, int end) { 
        propagate(node, start, end);
        if (right < start || end < left) return defaultValue;
        if (left <= start && end <= right) return tree[node];

        int mid = start + (end - start) / 2;
        int leftValue = queryRange(left, right, 2* node, start, mid);
        int rightValue = queryRange(left, right, 2* node + 1, mid + 1, end);
        return sum(leftValue, rightValue);
    }

private:
    void propagate(int node, int start, int end) {
        if (lazy[node] == 0) return;
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        tree[node] += lazy[node] * (end - start + 1); // sum
        lazy[node] = 0;
    }
};
```


### Segment Tree Min

```cpp
#pragma once

inline int min(int a, int b) { return (a < b) ? a : b; }

struct SegmentTreeMin {
    int* tree, n;
    const int defaultValue = 1e6;

    SegmentTreeMin(int maxSize) { n = maxSize; tree = new int[4 * n]; }
    ~SegmentTreeMin() { delete[] tree; }

    int build(int arr[], int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];

        int mid = start + (end - start) / 2;
        int leftValue = build(arr, 2 * node, start, mid);
        int rightValue = build(arr, 2 * node + 1, mid + 1, end);
        return tree[node] = min(leftValue, rightValue);
    }
    int updatePoint(int idx, int delta, int node, int start, int end) {
        if (idx < start || end < idx) return tree[node];
        if (start == end) return tree[node] += delta;

        int mid = start + (end - start) / 2;
        int leftValue = updatePoint(idx, delta, 2* node, start, mid);
        int rightValue = updatePoint(idx, delta, 2* node + 1, mid + 1, end);
        return tree[node] = min(leftValue, rightValue);
    }
    int queryRange(int left, int right, int node, int start, int end) { 
        if (right < start || end < left) return defaultValue;
        if (left <= start && end <= right) return tree[node];

        int mid = start + (end - start) / 2;
        int leftValue = queryRange(left, right, 2* node, start, mid);
        int rightValue = queryRange(left, right, 2* node + 1, mid + 1, end);
        return min(leftValue, rightValue);
    }
};

struct SegmentTreeMinLazy {
    int* tree, * lazy, n;
    const int defaultValue = 1e6;

    SegmentTreeMinLazy(int maxSize) { 
        n = maxSize;
        tree = new int[4 * n];
        lazy = new int[4 * n];
    }
    ~SegmentTreeMinLazy() { delete[] tree; delete[] lazy; }

    int build(int arr[], int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];

        int mid = start + (end - start) / 2;
        int leftValue = build(arr, 2 * node, start, mid);
        int rightValue = build(arr, 2 * node + 1, mid + 1, end);
        return tree[node] = min(leftValue, rightValue);
    }
    int updatePoint(int idx, int delta, int node, int start, int end) {
        if (idx < start || end < idx) return tree[node];
        if (start == end) return tree[node] += delta;

        int mid = start + (end - start) / 2;
        int leftValue = updatePoint(idx, delta, 2* node, start, mid);
        int rightValue = updatePoint(idx, delta, 2* node + 1, mid + 1, end);
        return tree[node] = min(leftValue, rightValue);
    }
    int updateRange(int left, int right, int delta, int node, int start, int end) {
        propagate(node, start, end);
        if (right < start || end < left) return tree[node];
        if (left <= start && end <= right) {
            if (start != end) {
                lazy[2 * node] += delta;
                lazy[2 * node + 1] += delta;
            }
            return tree[node] += delta;     // min
        }
        int mid = start + (end - start) / 2;
        int leftValue = updateRange(left, right, delta, 2* node, start, mid);
        int rightValue = updateRange(left, right, delta, 2* node + 1, mid + 1, end);
        return tree[node] = min(leftValue, rightValue);

    }
    int queryRange(int left, int right, int node, int start, int end) { 
        propagate(node, start, end);
        if (right < start || end < left) return defaultValue;
        if (left <= start && end <= right) return tree[node];

        int mid = start + (end - start) / 2;
        int leftValue = queryRange(left, right, 2* node, start, mid);
        int rightValue = queryRange(left, right, 2* node + 1, mid + 1, end);
        return min(leftValue, rightValue);
    }

private:
    void propagate(int node, int start, int end) {
        if (lazy[node] == 0) return;
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        tree[node] += lazy[node];   // min
        lazy[node] = 0;
    }
};
```

### main.cpp

```cpp
#include "segment_tree_min.h"
#include "segment_tree_sum.h"
#include <cstdio>

template<typename T>
void testSegTree(T& seg) {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int left = 0, right = n - 1, res;

    printf("\n");
    seg.build(arr, 1, 0, n - 1);

    res = seg.queryRange(left, right, 1, 0, n - 1);
    printf(">> Query[%d:%d] = %d\n", left, right, res);

    seg.updatePoint(0, 10, 1, 0, n - 1);          // arr[0] = 3
    res = seg.queryRange(left, right, 1, 0, n - 1);
    printf(">> Query[%d:%d] = %d\n", left, right, res);

    left = right = 0;
    res = seg.queryRange(left, right, 1, 0, n - 1);
    printf(">> Query[%d:%d] = %d\n", left, right, res);   // arr[0] = 3
}

int main()
{
    SegmentTreeSumLazy seg1(10);
    SegmentTreeMinLazy seg2(10);

    testSegTree(seg1);
    testSegTree(seg2);

    return 0;
}
```
