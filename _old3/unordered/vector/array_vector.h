#pragma once

template<typename T>
struct array_vector_static {
    T* arr;
    int cnt;

    array_vector_static(int arrSize=100) { arr = new T[arrSize]; cnt = 0; }
    ~array_vector_static() { delete[] arr; }

    void clear() { cnt = 0; }
    void push_back(const T& data) { arr[cnt++] = data; }
    T front() { return arr[0]; }
    T back() { return arr[cnt - 1]; }
    bool empty() { return cnt == 0; }
    int size() { return cnt; }

    // T* begin() { return arr; }
    // T* end() { return arr + cnt; }

    struct Iterator {
        int* ptr;
        Iterator(int* p) : ptr(p) {}
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; } // prefix
    };
    Iterator begin() { return Iterator(arr); }
    Iterator end() { return Iterator(arr + cnt); }
};

template<typename T>
struct array_vector_dynamic {
    T* arr;
    int cnt;
    int capacity;

    array_vector_dynamic(int arrSize = 100) {
        arr = new int[arrSize];
        cnt = 0;
        capacity = arrSize;
    }
    ~array_vector_dynamic() { delete[] arr; }

    void clear() { cnt = 0; }

    void resize(int newCapacity) {
        int* newArr = new int[newCapacity];
        for (int i = 0; i < cnt; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }
    void push_back(const T& data) {
        if (cnt == capacity) resize(capacity * 2);
        arr[cnt++] = data;
    }

    T front() { return arr[0]; }
    T back() { return arr[cnt - 1]; }
    bool empty() { return cnt == 0; }
    int size() { return cnt; }

    // Iterator
    struct Iterator {
        int* ptr;
        Iterator(int* p) : ptr(p) {}
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; } // prefix
    };
    Iterator begin() { return Iterator(arr); }
    Iterator end() { return Iterator(arr + cnt); }
};