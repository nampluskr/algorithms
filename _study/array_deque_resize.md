### Array

```cpp
#pragma once

template<typename T>
struct ArrayList {
    T* arr;
    int arrSize;
    int capacity;

    ArrayList(int capacity = 1) {
        arr = new T[capacity];
        arrSize = 0;
        this->capacity = capacity;
    }
    ~ArrayList() { delete[] arr; }

    void clear() { arrSize = 0; }

    void resize(int capacity) {
        if (capacity <= this->capacity) return;
        T* newArray = new T[capacity];
        for (int i = 0; i < arrSize; ++i) newArray[i] = arr[i];
        delete[] arr;
        arr = newArray;
        this->capacity = capacity;
    }

    void push_back(const T& data) {
        if (arrSize == capacity) resize(capacity * 2);
        arr[arrSize++] = data;
    }

    bool empty() { return arrSize == 0; }
    int size() { return arrSize; }

    T& operator[](int index) { return arr[index]; }
    const T& operator[](int index) const { return arr[index]; }

    T* begin() { return arr; }
    T* end() { return arr + arrSize; }

    //struct Iterator {
    //    T* ptr;

    //    // 이터레이터 생성자
    //    Iterator(T* p) : ptr(p) {}

    //    // 이터레이터 증가 연산자
    //    Iterator& operator++() { ++ptr; return *this; }
    //    Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }

    //    // 이터레이터 감소 연산자
    //    Iterator& operator--() { --ptr; return *this; }
    //    Iterator operator--(int) { Iterator temp = *this; --(*this); return temp; }

    //    T& operator*() const { return *ptr; } // 복사연산자
    //    T* operator->() const { return ptr; }

    //    bool operator==(const Iterator& other) const { return ptr == other.ptr; }
    //    bool operator!=(const Iterator& other) const { return !(*this == other); }
    //};

    //Iterator begin() { return Iterator(arr); }
    //Iterator end() { return Iterator(arr + arrSize); }
};

```

### Deque

```cpp
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

    T front() { return empty() ? -1 : arr[head]; }
    T back() { return empty() ? -1 : arr[(tail + capacity) % capacity]; }

    void resize(int newCapacity) {
        if (newCapacity <= capacity) return;
        T* newArray = new T[newCapacity];
        for (int i = 0; i < size(); i++) newArray[i] = arr[(head + i) % capacity];
        delete[] arr;
        arr = newArray;
        capacity = newCapacity;
        head = 0; tail = arrSize - 1;
    }

    void push_front(const T& data) {
        if (arrSize == capacity) resize(capacity * 2);
        head = (head - 1 + capacity) % capacity;
        arr[head] = data;
        arrSize++;
    }

    void pop_front() {
        if (empty()) return;
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
        if (empty()) return;
        tail = (tail - 1 + capacity) % capacity;
        arrSize--;
    }

    // 참조 연산자
    T& operator[](int index) { return arr[(head + index) % capacity]; }
    const T& operator[](int index) const { return arr[(head + index) % capacity]; }
};
```

### main

```cpp
#include "array.h"
#include "deque.h"
#include <vector>
#include <cstdio>
#include <deque>

template<typename T>
void testVector(T& vec) {
    printf("\n");
    vec.clear();
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);
    printf(">> size=%d\n", (int)vec.size());

    printf(">> ");
    for (const auto& x : vec) printf("[%d] ", x);
    printf("\n");

    printf(">> ");
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) printf("[%d] ", *iter);
    printf("\n");

    vec.clear();
    printf(">> size=%d\n", (int)vec.size());
}

template<typename T>
void testDeque(T& deq) {
    printf("\n");
    deq.clear(); deq.info();

    deq.push_front(10); deq.info();
    deq.push_front(20); deq.info();
    deq.push_front(30); deq.info();
    deq.push_front(40); deq.info();
    deq.push_front(50); deq.info();
    deq.push_front(60); deq.info();
    deq.push_front(70); deq.info();
    deq.push_front(80); deq.info();
    deq.push_front(90); deq.info();

    printf(">> size=%d\n", (int)deq.size());

    //printf(">> ");
    while (!deq.empty()) {
        auto data = deq.front(); deq.pop_front();
        printf("[%d] ", data); deq.info();
    }
    printf("\n");

    deq.clear(); deq.info();
    deq.push_back(10); deq.info();
    deq.push_back(20); deq.info();
    deq.push_back(30); deq.info();
    deq.push_back(40); deq.info();
    deq.push_back(50); deq.info();
    deq.push_back(60); deq.info();
    deq.push_back(70); deq.info();
    deq.push_back(80); deq.info();
    deq.push_back(90); deq.info();
    printf(">> size=%d\n", (int)deq.size());

    //printf(">> ");
    while (!deq.empty()) {
        auto data = deq.back(); deq.pop_back();
        printf("[%d] ", data); deq.info();
    }
    printf("\n");
}

int main()
{
    //std::vector<int> v0;
    //ArrayList<int> v1;

    //testVector(v0);
    //testVector(v1);

    //std::deque<int> d0;
    ArrayDeque<int> d1;

    //testDeque(d0);
    testDeque(d1);


    return 0;
}
```
