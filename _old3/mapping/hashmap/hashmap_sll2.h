#pragma once

template<typename T>
struct LinkedList {
    struct Node { T data; Node* next; };
    Node* head;

    LinkedList() { head = nullptr; }
    ~LinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    Node* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    void emplace(const T& data) {
        head = new Node{ data, head };  // push_front
    }
    void erase(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return; // No data
        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
};

template<typename K, typename V>
struct HashTable2 {
    struct Pair { 
        K key;
        V value;
        bool operator==(const Pair& other) const { return key == other.key; }
    };
    LinkedList<Pair>* table;
    // SLLSet<Pair>* table;
    // BSTSet<Pair>* table;
    int tableSize;

    HashTable2(int tableSize) {
        this->tableSize = tableSize;
        table = new LinkedList<Pair>[tableSize];
    }
    ~HashTable2() { clear(); delete[] table; }

    void clear() {
        for (int i = 0; i < tableSize; i++)
            table[i].clear();
    }
    int hashFunc(const K& key, int tableSize) {
        return key % tableSize;
    }
    V* find(const K& key) {
        int index = hashFunc(key, tableSize);
        auto res = table[index].find({ key, {} });
        return (res == nullptr) ? nullptr : &res->data.value;
    }
    void emplace(const K& key, const V& value) {
        int index = hashFunc(key, tableSize);
        table[index].emplace({ key, value });
    }
    void erase(const K& key) {
        int index = hashFunc(key, tableSize);
        table[index].erase({ key, {} });
    }
    V& operator[](const K& key) {
        int index = hashFunc(key, tableSize);
        auto res = table[index].find({ key, {} });
        if (res == nullptr) {
            table[index].emplace({ key, {} });
            res = table[index].find({ key, {} });
        }
        return res->data.value;
    }
};