#pragma once


template<typename T>
struct ArrayList {
    T* arr;
    int capacity;
    int arrSize;

    ArrayList(int initCapacity = 1) {
        arr = new T[initCapacity];
        capacity = initCapacity;
        arrSize = 0;
    }
    ~ArrayList() { delete[] arr; }

    void push_back(const T& data) {
        if (arrSize == capacity) resize(capacity * 2);
        arr[arrSize++] = data;
    }
    void pop_back() { arrSize--; }

    T* find(const T& data) {
        for (int i = 0; i < arrSize; ++i)
            if (arr[i] == data) return &arr[i];
        return nullptr;
    }
    void remove(const T& data) {
        T* target = find(data);
        if (target != nullptr) {
            for (int i = *target - arr; i < arrSize - 1; ++i)
                arr[i] = arr[i + 1];
            arrSize--;
        }
    }
    void resize(int newCapacity) {
        if (newCapacity < arrSize) return;
        T* temp = new int[newCapacity];
        for (int i = 0; i < arrSize; ++i) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
        capacity = newCapacity;
    }

    void clear() { arrSize = 0; }
    bool empty() { return arrSize == 0; }
    int size() { return arrSize; }
    T back() { return arr[arrSize - 1]; }

    T* begin() { return arr; }
    T* end() { return arr + arrSize; }

    T& operator[](int index) { return arr[index]; }
    const T& operator[](int index) const { return arr[index]; }
};
