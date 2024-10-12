#pragma once

template<typename K, typename V>
struct LinkedPairList {
    struct Node {
        K key;
        V value;
        Node* next;
    };
    Node* head;

    LinkedPairList() { head = nullptr; }
    ~LinkedPairList() { clear(); }

    void clear() {
        while (head != nullptr) {
            // Node* temp = head;
            // head = head->next;
            // delete = temp;
            Node* next = head->next;
            delete head;
            head = next;
        }
    }
    Node* find(const K& key) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->key == key) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    // push_front
    void emplace(const K& key, const V& value) {
        head = new Node{ key, value, head };

        // Node* node = find(key);
        // if (node != nullptr) node->value = value; // update
        // else {
        //     head = new Node{ key, value, head };
        //     // Node* newNode = new Node{ key, value, nullptr };
        //     // newNode->next = head;
        //     // head = newNode;
        // }
    }
    void erase(const K& key) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->key == key) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return; // No key
        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
};

template<typename K, typename V>
struct HashTable {
    LinkedPairList<K, V>* table;
    // OrderedList<K, V>* table;
    // BSTMap<K, V>* table;
    int tableSize;

    HashTable(int tableSize) {
        this->tableSize = tableSize;
        table = new LinkedPairList<K, V>[tableSize];
    }
    ~HashTable() { clear(); delete[] table; }

    void clear() {
        for (int i = 0; i < tableSize; i++)
            table[i].clear();
    }
    int hashFunc(const K& key, int tableSize) {
        return key % tableSize;
    }
    V* find(const K& key) {
        int index = hashFunc(key, tableSize);
        auto res = table[index].find(key);
        return (res == nullptr) ? nullptr : &res->value;
    }
    void emplace(const K& key, const V& value) {
        int index = hashFunc(key, tableSize);
        table[index].emplace(key, value);
    }
    void erase(const K& key) {
        int index = hashFunc(key, tableSize);
        table[index].erase(key);
    }
    V& operator[](const K& key) {
        int index = hashFunc(key, tableSize);
        auto res = table[index].find(key);
        if (res == nullptr) {
            table[index].emplace(key, {});
            res = table[index].find(key);
        }
        return res->value;
    }
};