#pragma once
#include <cstdio>

template<typename T>
struct array_stack {
    T* arr;
    int head, tail;
    int arrSize;

    array_stack(int arrSize) {
        this->arrSize = arrSize;
        arr = new T[arrSize];
        head = tail = 0;
    }
    ~array_stack() { delete[] arr; }

    // push_back
    void push(const T& data) {
        // if ((tail + 1) % arrSize == head) return;   // overflow
        arr[tail] = data;
        tail = (tail + 1) % arrSize;
    }
    // pop_back
    void pop() {
        // if (head == tail) return;    // empty
        tail = (tail - 1 + arrSize) % arrSize;
    }
    bool empty() { return head == tail; }
    void clear() { head = tail = 0; }
    T top() { return arr[tail - 1]; }
};