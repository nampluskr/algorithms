#pragma once

template <typename T>
struct array_deque {
    T* arr;
    int arrSize;
    int capacity;
    int head, tail;

    array_deque(int capacity = 1) {
        arr = new T[capacity];
        this->capacity = capacity;
        head = 0; tail = -1; arrSize = 0;
    }
    ~array_deque() { delete[] arr; }

    void clear() { head = 0; tail = -1; arrSize = 0; }
    bool empty() { return arrSize == 0; }
    int size() { return arrSize; }
    T front() { return arr[head]; }
    T back() { return arr[(tail + capacity) % capacity]; }

    void push_front(const T& data) {
        if (arrSize == capacity) resize(capacity * 2);
        head = (head - 1 + capacity) % capacity;
        arr[head] = data;
        arrSize++;
    }
    void pop_front() {
        head = (head + 1) % capacity;
        arrSize--;
    }
    void push_back(const T& data) {
        if (arrSize == capacity) resize(capacity * 2);
        tail = (tail + 1) % capacity;
        arr[tail] = data;
        arrSize++;
    }
    void pop_back() {
        tail = (tail - 1 + capacity) % capacity;
        arrSize--;
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