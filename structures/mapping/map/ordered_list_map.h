#pragma once

template<typename K, typename V>
struct OrderedListMap {
    struct Node {
        K key;
        V value;
        Node* next;
    };
    Node* head;

    OrderedListMap() { head = nullptr; }
    ~OrderedListMap() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    V* find(const K& key) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->key == key) return &curr->value;
            if (key < curr->key) curr = curr->next;
            else break;
        }
        return nullptr;
    }
    void emplace(const K& key, const V& value) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->key == key) return; // No duplicates
            if (key < curr->key) { prev = curr; curr = curr->next; }
            else break;
        }
        Node* newNode = new Node{ key, value, curr };
        if (prev == nullptr) head = newNode;
        else prev->next = newNode;
    }
    void erase(const K& key) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->key == key) break;
            if (key < curr->key) { prev = curr; curr = curr->next; }
            else return;    // No key
        }
        if (curr == nullptr) return; // No key
        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
    V& operator[](const K& key) {
        V* res = find(key);
        if (res == nullptr) {
            emplace(key, V());
            res = find(key);
        }
        return *res;
    }
};