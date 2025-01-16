## Array

```cpp
template<typename T>
struct Array {
    T* arr;
    int tail = -1, capacity = 128;

    Array() { arr = new T[capacity]; }
    ~Array() { delete[] arr; }

    void clear() { tail = -1; }
    void push_back(const T& data) { 
        if (tail == capacity - 1) resize(capacity * 2);
        arr[++tail] = data;
    }
    int size() { return tail + 1; }

    // iterators
    T* begin() { return arr; }
    T* end() { return arr + tail + 1; }

private:
    void resize(int newCapacity) {
        if (newCapacity <= capacity) return;
        capacity = newCapacity;
        T* temp = new T[capacity];
        for (int i = 0; i <= tail; i++) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
    }
};
```

## Queue

```cpp
template<typename T>
struct Queue {
    T* arr;
    int head = 0, tail = -1, capacity = 128;

    Queue() { arr = new T[capacity]; }
    ~Queue() { delete[] arr; }

    void clear() { head = 0, tail = -1; }
    void push(const T& data) {
        if (tail == capacity - 1) resize(capacity * 2);
        arr[++tail] = data;
    }
    void pop() { head++; }
    T front() { return arr[head]; }
    bool empty() { return tail < head; }
    int size() { return tail - head + 1; }

    // iterators
    T* begin() { return arr + head; }
    T* end() { return arr + tail + 1; }

private:
    void resize(int newCapacity) {
        if (newCapacity <= capacity) return;
        capacity = newCapacity;
        T* temp = new T[capacity];
        for (int i = 0; i <= tail - head; i++) temp[i] = arr[head + i];
        delete[] arr;
        arr = temp;
        tail -= head;
        head = 0;
    }
};
```
