#pragma once

template<typename K, typename V, typename Map>
struct HashMap {
    Map* table;
    int maxTable;

    HashMap(int maxTable = 11) {
        table = new Map[maxTable];
        this->maxTable = maxTable;
    }
    ~HashMap() { clear();  delete[] table; }

    int hashFunc(const K& key) { return key % maxTable; }

    void clear() { 
        for (int i = 0; i < maxTable; i++) table[i].clear();
        maxTable = 0;
    }
    V* find(const K& key) {
        int index = hashFunc(key);
        return table[index].find(key);
    }
    void emplace(const K& key, const V& value) {
        int index = hashFunc(key);
        table[index].emplace(key, value);
    }
    void remove(const K& key) {
        int index = hashFunc(key);
        table[index].remove(key);
    }
    V& operator[](const K& key) {
        int index = hashFunc(key);
        V* res = table[index].find(key);
        if (res == nullptr) {
            table[index].emplace(key, V());
            res = table[index].find(key);
        }
        return *res;
    }
};

template<typename K, typename V>
struct HashChaining {
    struct Node {
        K key;
        V value;
        Node* next;
    };
    Node** table;
    int maxTable;

    HashChaining(int maxTable = 11) {
        table = new Node*[maxTable];
        for (int i = 0; i < maxTable; i++)
            table[i] = nullptr;
        this->maxTable = maxTable;
    }
    ~HashChaining() { clear(); delete[] table; }

    int hashFunc(const K& key) { return key % maxTable; }
    void clear() {
        for (int i = 0; i < maxTable; i++) {
            Node* curr = table[i];
            while (curr != nullptr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }
    V* find(const K& key) {
        int index = hashFunc(key);
        Node* curr = table[index];
        while (curr != nullptr) {
            if (curr->key == key) return &curr->value;
            curr = curr->next;
        }
        return nullptr;
    }
    void emplace(const K& key, const V& value) {
        //Node* curr = table[index];
        //while (curr != nullptr) {
        //    if (curr->key == key) { curr->value = value; return; }
        //    curr = curr->next;
        //}
        V* res = find(key);
        if (res != nullptr) { *res = value; return; }
        else {
            // push_front
            int index = hashFunc(key);
            Node* newNode = new Node{ key, value, nullptr };
            newNode->next = table[index];
            table[index] = newNode;
        }
    }
    void remove(const K& key) {
        int index = hashFunc(key);
        Node* prev = nullptr;
        Node* curr = table[index];
        while (curr != nullptr) {
            if (curr->key == key) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return;    // No data
        if (prev == nullptr) table[index] = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
    V& operator[](const K& key) {
        V* res = find(key);
        if (res == nullptr) {
            emplace(key, V());  // emplace(key, {});
            res = find(key);
        }
        return *res;
    }
};
