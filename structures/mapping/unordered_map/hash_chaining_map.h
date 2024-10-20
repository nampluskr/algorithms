#pragma once
#include "hash_func.h"

template<typename K, typename V, typename Map>
struct HashChainingMap {
    Map* table;
    int maxTable;

    HashChainingMap(int maxTable = 11) {
        table = new Map[maxTable];
        this->maxTable = maxTable;
    }
    ~HashChainingMap() { clear();  delete[] table; }

    // Hash Function
    int hashFunc(const K& key) { return hash_func<K>(key, maxTable); }

    void clear() {
        for (int i = 0; i < maxTable; i++)
            table[i].clear();
    }
    V* find(const K& key) {
        int index = hashFunc(key);
        return table[index].find(key);
    }
    void emplace(const K& key, const V& value) {
        int index = hashFunc(key);
        table[index].emplace(key, value);
    }
    void erase(const K& key) {
        int index = hashFunc(key);
        table[index].erase(key);
    }
    V& operator[](const K& key) {
        int index = hashFunc(key);
        V* res = table[index].find(key);
        if (res == nullptr) {
            table[index].emplace(key, V()); // table[index].emplace(key, {});
            res = table[index].find(key);
        }
        return *res;
    }
};
