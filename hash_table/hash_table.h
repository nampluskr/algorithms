#pragma once
#include "linked_list.h"
#include "hash_func.h"

template<typename Key, typename Value>
struct HashTable {
    struct Pair {
        Key key;
        Value value;
        bool operator==(const Pair& pair) const { return key == pair.key; }
    };
    LinkedList<Pair>* table;
    int maxTable;

    HashTable(int maxTable) {
        this->maxTable = maxTable;
        table = new LinkedList<Pair>[maxTable];
    }
    ~HashTable() { clear(); delete[] table; }

    void clear() {
        for (int i = 0; i < maxTable; i++)
            table[i].clear();
    }
    Pair* emplace(const Key& key, const Value& value) {
        int index = hashFunc<Key>(key, maxTable);
        table[index].push_back({ key, value });
        return &table[index].tail->data;
    }
    Pair* find(const Key& key) {
        int index = hashFunc<Key>(key, maxTable);
        return &table[index].find({ key, {} })->data;
    }
    void remove(const Key& key) {
        int index = hashFunc<Key>(key, maxTable);
        table[index].remove({ key, {} });
    }
    void push(const Pair& pair) { emplace(pair.key, pair.value); }
    Value& operator[](const Key& key) {
        Pair* data = find(key);
        if (data == nullptr) data = emplace(key, {});
        return data->value;
    }
};