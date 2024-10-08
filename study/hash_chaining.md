### [Template]

```cpp
#pragma once

// HashMap: K -> V
// Hash Chaing with Linked List

template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;

    LinkedList() { head = tail = nullptr; }
    ~LinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    Node* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    // for (Iterator iter = begin(); iter != end(); ++iter) { *iter }
    struct Iterator {
        Node* ptr;
        Iterator(Node* ptr = nullptr) { this->ptr = ptr; }
        bool operator!=(const Iterator& iter) const { return ptr != iter.ptr; }
        int& operator*() { return ptr->data; }
        Iterator& operator++() { ptr = ptr->next; return *this; }
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

int hashFunc(const K& key) {
    return key % capacity;
}

template<typename K, typename V>
struct HashTable {
    struct Pair {
        K key;
        V value;
        bool operator==(const Pair& other) const { return key == other.key; }
    };
    LinkedList<Pair>* table;
    int capacity;

    HashTable(int max_size) { 
        capacity = max_size;
        table = new LinkedList<Pair>[capacity];
    }
    ~HashTable() { clear(); delete[] table; }

    void clear() {
        for (int i = 0; i < capacity; i++)
            table[i].clear();
    }
    Pair* emplace(const K& key, const V& value) {
        int idx = hashFunc<K>(key);
        table[idx].push_back({ key, value });
        return &table[idx].tail->data;
    }
    void push(const Pair& data) {
        emplace(data.key, data.value);
    }
    Pair* find(const K& key) {
        int idx = hashFunc<K>(key);
        return &table[idx].find({ key, {} })->data;
    }
    V& operator[](const K& key) {
        Pair* data = find(key);
        if (data == nullptr) data = emplace(key, {});
        return data->value;
    }
};
```

### [hash_chaining.h]

```cpp
#pragma once

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = tail = nullptr;
    }
    void push_back(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; };
    }
    Node<T>* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
};

template<typename Key, typename Value>
struct Pair { 
    Key key;
    Value value;
    bool operator==(const Pair& pair) const { return key == pair.key; }
};

template<typename Key, typename Value>
struct HashTable {
    LinkedList<Pair<Key, Value>>* table;

    HashTable(int max_size) { table = new LinkedList<Pair<Key, Value>>[max_size]; }
    ~HashTable() { 
        int max_size = sizeof(table) / sizeof(LinkedList<Pair<key, Value>>*);
        for (int i = 0; i < max_size; i++) table[i].clear();
        delete[] table;
    }

    int hashFunc(const Key& key) {
        return (key * 31) % 5931;
    }
    void emplace(const Key& key, const Value& value) {
        int index = hashFunc(key);
        table[index].push_back({ key, value });
    }
    Node<Pair<Key, Value>>* find(const Key& key) {
        int index = hashFunc(key);
        return table[index].find({ key, {} });
    }
    Value& operator[](const Key& key) {
        int index = hashFunc(key);
        Node<Pair<Key, Value>>* node = table[index].find({ key, {} });
        if (node != nullptr) return node->data.value;
        else {
            table[index].push_back({ key, {} });
            return table[index].tail->data.value;
        }
    }
};
```
