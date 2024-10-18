#pragma once
#include <cstdio>

template<typename T>
struct array_queue {
    T* arr;
    int head, tail;
    int arrSize;

    array_queue(int arrSize) {
        this->arrSize = arrSize;
        arr = new T[arrSize];
        head = tail = 0;
    }
    ~array_queue() { delete[] arr; }

    // pop_front
    void pop() {
        // if (head == tail) return;    // empty
        head = (head + 1) % arrSize;
    }
    // push_back
    void push(const T& data) {
        // if ((tail + 1) % arrSize == head) return;   // overflow
        arr[tail] = data;
        tail = (tail + 1) % arrSize;
    }
    bool empty() { return head == tail; }
    void clear() { head = tail = 0; }
    T front() { return arr[head]; }
};