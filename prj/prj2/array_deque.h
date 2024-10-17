#pragma once

#pragma once
#include <cstdio>

template <typename T>
struct ArrayDeque {
    T* arr;
    int arrSize;
    int capacity;
    int head, tail;

    ArrayDeque(int initCapacity = 1) {
        arr = new T[initCapacity];
        capacity = initCapacity;
        head = 0; tail = -1;
        arrSize = 0;
    }
    ~ArrayDeque() { delete[] arr; }

    void info() {
        printf(">> [size %2d]: head %2d, tail %2d, capacity %2d [head:%2d / tail:%2d]\n", size(), head, tail, capacity, front(), back());
    }

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
    void resize(int newCapacity) {
        if (newCapacity < arrSize) return;
        T* newArray = new T[newCapacity];
        for (int i = 0; i < arrSize; i++) newArray[i] = arr[(head + i) % capacity];
        delete[] arr;
        arr = newArray;
        capacity = newCapacity;
        head = 0; tail = arrSize - 1;
    }
};

template <typename T>
struct ArrayStack {
    T* arr;
    int arrSize;
    int capacity;
    int tail;

    ArrayStack(int initCapacity = 1) {
        arr = new T[initCapacity];
        capacity = initCapacity;
        tail = -1;
        arrSize = 0;
    }
    ~ArrayStack() { delete[] arr; }

    void clear() { tail = -1; arrSize = 0; }
    bool empty() { return arrSize == 0; }
    int size() { return arrSize; }

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
    void resize(int newCapacity) {
        if (newCapacity < arrSize) return;
        T* newArray = new T[newCapacity];
        for (int i = 0; i < arrSize; i++) newArray[i] = arr[i];
        delete[] arr;
        arr = newArray;
        capacity = newCapacity;
        tail = arrSize - 1;
    }
};

template <typename T>
struct ArrayQueue {
    T* arr;
    int arrSize;
    int capacity;
    int head, tail;

    ArrayQueue(int initCapacity = 1) {
        arr = new T[initCapacity];
        capacity = initCapacity;
        head = 0; tail = -1;
        arrSize = 0;
    }
    ~ArrayQueue() { delete[] arr; }

    void clear() { head = 0; tail = -1; arrSize = 0; }
    bool empty() { return arrSize == 0; }
    int size() { return arrSize; }

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
    void resize(int newCapacity) {
        if (newCapacity < arrSize) return;
        T* newArray = new T[newCapacity];
        for (int i = 0; i < arrSize; i++) newArray[i] = arr[(head + i) % capacity];
        delete[] arr;
        arr = newArray;
        capacity = newCapacity;
        head = 0; tail = arrSize - 1;
    }
};
