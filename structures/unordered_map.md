### Array & Unordered Map

```cpp
#include <cstdio>
//#include <vector>
#include <unordered_map>
using namespace std;


template<typename T>
struct Array {
    T* arr;
    int tail = -1, capacity = 1;

    Array() { arr = new T[capacity]; }                  // 생성자
    ~Array() { delete[] arr; }                          // 소멸자

    Array(const Array& other) {                         // 복사 생성자
        tail = other.tail;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i <= tail; i++) arr[i] = other.arr[i];
    }
    Array& operator=(const Array& other) {              // 복사 대입 연산자
        if (this != &other) {
            delete[] arr;
            tail = other.tail;
            capacity = other.capacity;
            arr = new T[capacity];
            for (int i = 0; i <= other.tail; i++) arr[i] = other.arr[i];
        }
        return *this;
    }

    void clear() { tail = -1; }
    void push_back(const T& data) {
        if (tail == capacity - 1) resize(capacity * 2);
        arr[++tail] = data;
    }
    T* begin() { return arr; }                          // 이터레이터
    T* end() { return arr + tail + 1; }                 // 이터레이터
    T& operator[](int idx) { return arr[idx]; }         // 참조 연산자

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


#define MAX_TABLE 1007

int hashFunc(int key) {
    return key % MAX_TABLE;
}


template<typename K, typename V>
struct UnorderedMap {
    struct Pair {
        K first;
        V second;
    };
    Array<Pair> table[MAX_TABLE];

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i].clear();
    }
    void emplace(const K& key, const V& value) {
        int idx = hashFunc(key);
        table[idx].push_back({ key, value });
    }
    void insert(const Pair& pair) {
        emplace(pair.first, pair.second);
    }
    Pair* find(const K& key) {
        int idx = hashFunc(key);
        for (auto& pair : table[idx])
            if (pair.first == key) return &pair;
        return nullptr;
    }
    Pair* end() { return nullptr; }
    V& operator[](const K& key) {
        auto res = find(key);
        if (res == end()) { emplace(key, {}); res = find(key); }
        return res->second;
    }
};


struct Data { int num; } data[101];
int dataCnt;
unordered_map<int, int> umap;

template<typename K>
int getIndex(const K& key) {
    int idx;
    auto res = umap.find(key);
    if (res == umap.end()) {
        idx = dataCnt++;
        umap.emplace(key, idx);
    }
    else { idx = res->second; }
    return idx;
}


int main()
{
    if (1) {
        UnorderedMap<int, int> intMap;

        intMap.emplace(1000, 1);
        intMap.emplace(2000, 2);
        intMap.emplace(3000, 3);

        printf("\n");
        printf("%d, %d\n", 1000, intMap[1000]);
        printf("%d, %d\n", 2000, intMap[2000]);
        printf("%d, %d\n", 3000, intMap[3000]);
        printf("%d, %d\n", 4000, intMap[4000]);

        intMap.clear();
    }

    if (1) {
        UnorderedMap<int, Array<int>> listMap;

        listMap[1000].push_back(1);
        listMap[1000].push_back(2);
        listMap[1000].push_back(3);
        listMap[1000].push_back(4);
        listMap[1000].push_back(5);

        printf("\n");
        for (int x : listMap[1000]) printf("%d ", x);
        printf("\n");

        listMap[2000].push_back(10);
        listMap[2000].push_back(20);
        listMap[2000].push_back(30);
        listMap[2000].push_back(40);
        listMap[2000].push_back(50);

        printf("\n");
        for (int x : listMap[2000]) printf("%d ", x);
        printf("\n");

        listMap.clear();
    }

    if (1) {
        dataCnt = 0;
        int key;

        printf("\n");
        key = 100; printf("%d %d\n", key, getIndex(key));
        key = 200; printf("%d %d\n", key, getIndex(key));
        key = 300; printf("%d %d\n", key, getIndex(key));

        key = 100; printf("%d %d\n", key, getIndex(key));
        key = 200; printf("%d %d\n", key, getIndex(key));
        key = 300; printf("%d %d\n", key, getIndex(key));

        umap.clear();
    }

    return 0;
}
```
