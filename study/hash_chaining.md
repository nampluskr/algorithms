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
