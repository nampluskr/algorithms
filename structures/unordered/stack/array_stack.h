#pragma once

template <typename T>
struct ArrayStack {
    T* arr;
    int arrSize;
    int capacity;
    int tail;

    ArrayStack(int capacity = 1) {
        arr = new T[capacity];
        this->capacity = capacity;
        tail = -1;
        arrSize = 0;
    }
    ~ArrayStack() { delete[] arr; }

    void clear() { tail = -1; arrSize = 0; }
    bool empty() { return arrSize == 0; }
    T top() { return arr[(tail + capacity) % capacity]; }

    // push_back
    void push(const T& data) {
        if (arrSize == capacity) resize(capacity * 2);
        tail = (tail + 1) % capacity;
        arr[tail] = data;
        arrSize++;
    }
    // pop_back
    void pop() {
        tail = (tail - 1 + capacity) % capacity;
        arrSize--;
    }
private:
    void resize(int capacity) {
        if (capacity < arrSize) return;
        T* temp = new T[capacity];
        for (int i = 0; i < arrSize; i++) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
        this->capacity = capacity;
        tail = arrSize - 1;
    }
};