#pragma once

template<typename T>
struct ArrayList {
    T* arr;
    int capacity;
    int arrSize;

    ArrayList(int capacity = 1) {
        arr = new T[capacity];
        this->capacity = capacity;
        arrSize = 0;
    }
    ~ArrayList() { delete[] arr; }

    void clear() { arrSize = 0; }
    bool empty() { return arrSize == 0; }
    int size() { return arrSize; }
    T back() { return arr[arrSize - 1]; }

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

    // Iterator
    T* begin() { return arr; }
    T* end() { return arr + arrSize; }

    // 참조 연산자
    T& operator[](int index) { return arr[index]; }
    const T& operator[](int index) const { return arr[index]; }

private:
    void resize(int capacity) {
        if (capacity < arrSize) return;
        T* temp = new int[capacity];
        for (int i = 0; i < arrSize; ++i) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
        this->capacity = capacity;
    }
};