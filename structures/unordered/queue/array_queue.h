#pragma once

template <typename T>
struct ArrayQueue {
    T* arr;
    int arrSize;
    int capacity;
    int head, tail;

    ArrayQueue(int capacity = 1) {
        arr = new T[capacity];
        this->capacity = capacity;
        head = 0; tail = -1;
        arrSize = 0;
    }
    ~ArrayQueue() { delete[] arr; }

    void clear() { head = 0; tail = -1; arrSize = 0; }
    bool empty() { return arrSize == 0; }
    T front() { return arr[head]; }

    // pop_front
    void pop() {
        head = (head + 1) % capacity;
        arrSize--;
    }
    // push_back
    void push(const T& data) {
        if (arrSize == capacity) resize(capacity * 2);
        tail = (tail + 1) % capacity;
        arr[tail] = data;
        arrSize++;
    }

private:
    void resize(int capacity) {
        if (capacity < arrSize) return;
        T* temp = new T[capacity];
        for (int i = 0; i < arrSize; i++)
            temp[i] = arr[(head + i) % this->capacity];
        delete[] arr;
        arr = temp;
        this->capacity = capacity;
        head = 0; tail = arrSize - 1;
    }
};
