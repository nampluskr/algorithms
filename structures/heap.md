## Binary Heap: MaxHeap / MinHeap

```cpp
#include <cstdio>
#include <queue>
using namespace std;

struct Data {
    int value1, value2;

    bool operator<(const Data& other) const {
        return (value1 < other.value1) || (value1 == other.value1 && value2 < other.value2);
    }
    bool operator>(const Data& other) const {
        return (value1 > other.value1) || (value1 == other.value1 && value2 > other.value2);
    }
};

template<typename T>
struct BinaryHeap {
    T* heap;
    int heapSize = 0, capacity = 1;

    BinaryHeap() { heap = new T[capacity]; }
    virtual ~BinaryHeap() = default;        // 가상 소멸자 (추상 클래스)
    //~BinaryHeap() { delete[] heap; }

    // 복사 생성자
    BinaryHeap(const BinaryHeap& other) {
        heapSize = other.heapSize;
        capacity = other.capacity;
        heap = new T[capacity];
        for (int i = 0; i < heapSize; i++) heap[i] = other.heap[i];
    }
    // 복사 대입 연산자
    BinaryHeap& operator=(const BinaryHeap& other) {
        if (this != &other) {
            delete[] heap;
            heapSize = other.heapSize;
            capacity = other.capacity;
            heap = new T[capacity];
            for (int i = 0; i < heapSize; i++) heap[i] = other.heap[i];
        }
        return *this;
    }

    void push(const Data& data) {
        if (heapSize == capacity) resize(capacity * 2);
        heap[heapSize] = data;
        siftUp(heapSize);
        heapSize++;
    }
    void pop() {
        heapSize--;
        swap(heap[0], heap[heapSize]);
        siftDown(0);
    }
    bool empty() { return heapSize == 0; }
    T top() { return heap[0]; }

    virtual void siftUp(int curr) = 0;
    virtual void siftDown(int curr) = 0;

private:
    void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
    void resize(int newCapacity) {
        if (newCapacity <= capacity) return;
        capacity = newCapacity;
        T* temp = new T[capacity];
        for (int i = 0; i < heapSize; i++) temp[i] = heap[i];
        delete[] heap;
        heap = temp;
    }
};

template<typename T>
struct MaxHeap : BinaryHeap<T> {
    using BinaryHeap<T>::heap;      // heap 변수에 접근할 수 있도록 함
    using BinaryHeap<T>::heapSize;  // heapSize 변수에 접근할 수 있도록 함

    ~MaxHeap() { delete[] heap; }

    void siftUp(int curr) override {
        int parent = (curr - 1) / 2; // parent index
        while (curr > 0) {
            if (heap[curr] < heap[parent]) break;

            swap(heap[curr], heap[parent]);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
    void siftDown(int curr) override {
        int child = 2 * curr + 1;    // left child index
        while (child < heapSize) {
            if (child + 1 < heapSize && heap[child] < heap[child + 1]) child++;
            if (heap[child] < heap[curr]) break;

            swap(heap[child], heap[curr]);
            curr = child;
            child = 2 * curr + 1;
        }
    }
};

template<typename T>
struct MinHeap : BinaryHeap<T> {
    using BinaryHeap<T>::heap;      // heap 변수에 접근할 수 있도록 함
    using BinaryHeap<T>::heapSize;  // heapSize 변수에 접근할 수 있도록 함

    ~MinHeap() { delete[] heap; }

    void siftUp(int curr) override {
        int parent = (curr - 1) / 2; // parent index
        while (curr > 0) {
            if (heap[curr] > heap[parent]) break;

            swap(heap[curr], heap[parent]);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
    void siftDown(int curr) override {
        int child = 2 * curr + 1;    // left child index
        while (child < heapSize) {
            if (child + 1 < heapSize && heap[child] > heap[child + 1]) child++;
            if (heap[child] > heap[curr]) break;

            swap(heap[child], heap[curr]);
            curr = child;
            child = 2 * curr + 1;
        }
    }
};


int main()
{
    //priority_queue<Data> pq;
    MaxHeap<Data> maxPQ;

    maxPQ.push({ 30, 100 });
    maxPQ.push({ 10, 100 });
    maxPQ.push({ 20, 100 });
    maxPQ.push({ 30, 200 });
    maxPQ.push({ 10, 200 });
    maxPQ.push({ 20, 200 });

    printf("\n");
    while (!maxPQ.empty()) {
        auto data = maxPQ.top(); maxPQ.pop();
        printf("(%d, %d)\n", data.value1, data.value2);
    }

    //priority_queue<Data> pq;
    MinHeap<Data> minPQ;

    minPQ.push({ 30, 100 });
    minPQ.push({ 10, 100 });
    minPQ.push({ 20, 100 });
    minPQ.push({ 30, 200 });
    minPQ.push({ 10, 200 });
    minPQ.push({ 20, 200 });

    printf("\n");
    while (!minPQ.empty()) {
        auto data = minPQ.top(); minPQ.pop();
        printf("(%d, %d)\n", data.value1, data.value2);
    }

    return 0;
}
```
