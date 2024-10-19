#pragma once

template<typename T>
struct BinaryHeapPQ {
    T* heap;
    int heapSize;
    int capacity;

    BinaryHeapPQ(int capacity = 1) {
        heap = new T[capacity];
        heapSize = 0;
        this->capacity = capacity;
    }
    ~BinaryHeapPQ() { delete[] heap; }

    void clear() { heapSize = 0; }
    void push(const T& data) {
        if (heapSize == capacity) resize(capacity * 2);
        heap[heapSize] = data;
        siftUp(heapSize);
        heapSize++;
    }
    void pop() {
        heapSize--;
        swap(heap[0], heap[heapSize]);
        siftDown(0);
    }
    bool empty() { return heapSize == 0; }
    T top() { return heap[0]; }

private:
#if 0
    // iterative methods (Reference)
    void siftUp(int index) {
        int curr = index;
        int parent = (curr - 1) / 2; // parent index
        while (curr > 0) {
            if (heap[curr] < heap[parent]) break;

            swap(heap[curr], heap[parent]);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
    void siftDown(int index) {
        int curr = index;
        int child = 2 * curr + 1;    // left child index
        while (child < heapSize) {
            if (child + 1 < heapSize && heap[child] < heap[child + 1]) child++;
            if (heap[child] < heap[curr]) break;

            swap(heap[child], heap[curr]);
            curr = child;
            child = 2 * curr + 1;
        }
    }
#else
    // recursive methods
    void siftUp(int index) {
        if (index <= 0) return;         // base condition
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) return;

        swap(heap[index], heap[parent]);
        siftUp(parent);
    }
    void siftDown(int index) {
        int child = 2 * index + 1;      // left child index
        if (child >= heapSize) return;  // base condition
        if (child + 1 < heapSize && heap[child] < heap[child + 1]) child++;
        if (heap[child] < heap[index]) return;

        swap(heap[child], heap[index]);
        siftDown(child);
    }
#endif
    void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
    void resize(int capacity) {
        if (capacity < heapSize) return;
        T* temp = new T[capacity];
        for (int i = 0; i < heapSize; i++) temp[i] = heap[i];
        delete[] heap;
        heap = temp;
        this->capacity = capacity;
    }
};