#pragma once

template<typename K, typename V>
struct ListMap {
    struct Node {
        K key;
        V value;
        Node* next;
    };
    Node* head;

    ListMap() { head = nullptr; }
    ~ListMap() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    // O(n)
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
    V& operator[](const K& key) {
        auto res = find(key);
        if (res == nullptr) {
            emplace(key, {});
            res = find(key);
        }
        return res->value;
    }
};