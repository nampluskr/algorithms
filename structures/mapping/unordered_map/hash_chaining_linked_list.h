#pragma once
#include "hash_func.h"
#include "../../unordered/list/linked_list.h"

template<typename K, typename V>
struct HashChainingLinkedList {
    struct Pair {
        K key; V value;
        bool operator==(const Pair& other) { return key == other.key; }
    };
    LinkedList<Pair>* table;
    int maxTable;

    HashChainingLinkedList(int maxTable = 11) {
        table = new LinkedList<Pair>[maxTable];
        this->maxTable = maxTable;
    }
    ~HashChainingLinkedList() { clear();  delete[] table; }

    // Hash Function
    int hashFunc(const K& key) { return hash_func<K>(key, maxTable); }

    void clear() {
        for (int i = 0; i < maxTable; i++)
            table[i].clear();
    }
    Pair* find(const K& key) {
        int index = hashFunc(key);
        return table[index].find({ key, V() });
    }
    void emplace(const K& key, const V& value) {
        int index = hashFunc(key);
        Pair* res = table[index].find({ key, V() });
        if (res != nullptr) res->value = value;     // Updata
        else table[index].push_back({ key, value });
    }
    void erase(const K& key) {
        int index = hashFunc(key);
        table[index].remove({ key, V() });
    }
    V& operator[](const K& key) {
        Pair* res = find(key);
        if (res == nullptr) {
            emplace(key, V());
            res = find(key);
        }
        return res->value;
        // int index = hashFunc(key);
        // Pair* res = table[index].find({ key, V() });
        // if (res == nullptr) {
        //     table[index].push_back({ key, V() }); // table[index].push_back(key, {});
        //     res = table[index].find({ key, V() });
        // }
        // return res->value;
    }
};
