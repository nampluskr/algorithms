#pragma once
#include <cstdio>

template<typename T>
struct array_deque {
    T* arr;
    int head, tail;
    int arrSize;

    array_deque(int arrSize) {
        this->arrSize = arrSize;
        arr = new T[arrSize];
        head = tail = 0;
    }
    ~array_deque() { delete[] arr; }

    void push_front(const T& data) {
        // if ((tail + 1) % arrSize == head) return;   // overflow
        head = (head - 1 + arrSize) % arrSize;
        arr[head] = data;
    }
    void pop_front() {
        // if (head == tail) return;    // empty
        head = (head + 1) % arrSize;
    }
    void push_back(const T& data) {
        // if ((tail + 1) % arrSize == head) return;   // overflow
        arr[tail] = data;
        tail = (tail + 1) % arrSize;
    }
    void pop_back() {
        // if (head == tail) return;    // empty
        tail = (tail - 1 + arrSize) % arrSize;
    }
    bool empty() { return head == tail; }
    void clear() { head = tail = 0; }
    void show() const {
        printf(">> ");
        if (head != tail) {
            int curr = head;
            do {
                printf("[%d]->", arr[curr]);
                curr = (curr + 1) % arrSize;
            } while (curr != tail);
        }
        printf("\n");
    }
};