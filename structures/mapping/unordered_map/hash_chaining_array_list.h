#pragma once
#include "hash_func.h"
#include "../../unordered/list/array_list.h"

template<typename K, typename V>
struct HashChainingArrayList {
    struct Pair {
        K key; V value;
        bool operator==(const Pair& other) { return key == other.key; }
    }; 
    ArrayList<Pair>* table;
    int maxTable;

    HashChainingArrayList(int maxTable = 11) {
        table = new ArrayList<Pair>[maxTable];
        this->maxTable = maxTable;
    }
    ~HashChainingArrayList() { clear();  delete[] table; }

    // Hash Function
    int hashFunc(const K& key) { return hash_func<K>(key, maxTable); }

    void clear() {
        for (int i = 0; i < maxTable; i++)
            table[i].clear();
    }
    Pair* find(const K& key) {
        int index = hashFunc(key);
        int res = table[index].find({ key, V() });
        return (res == -1) ? nullptr : &table[index][res];
    }
    void emplace(const K& key, const V& value) {
        int index = hashFunc(key);
        int res = table[index].find({ key, value });
        if (res != -1) table[index][res].value = value;
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

    //     int index = hashFunc(key);
    //     int res = table[index].find({ key, V() });
    //     if (res == -1) {
    //         table[index].push_back({ key, V() });
    //         res = table[index].find({ key, V() });
    //     }
    //     return table[index][res].value;
    }
};
