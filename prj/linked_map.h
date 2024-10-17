#pragma once

template<typename K, typename V>
struct LinkedMap {
    struct Node {
        K key;
        V value;
        Node* next;
    };
    Node* head;

    LinkedMap() { head = nullptr; }
    ~LinkedMap() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    V* find(const K& key) {
        Node* res = findRecur(head, key);
        return (res == nullptr) ? nullptr : &res->value;
    }
    void emplace(const K& key, const V& value) { head = insertRecur(head, key, value); }
    void remove(const K& key) { head = removeRecur(head, key); }
    V& operator[](const K& key) {
        V* res = find(key);
        if (res == nullptr) {
            emplace(key, V());
            res = find(key);
        }
        return *res;
    }

private:
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;
    }
    Node* findRecur(Node* node, const K& key) {
        if (node == nullptr) return nullptr;
        if (node->key == key) return node;
        return findRecur(node->next, key);
    }
    Node* insertRecur(Node* node, const K& key, const V& value) {
        if (node == nullptr) return new Node{ key, value, nullptr };
        if (node->key == key) return node;    // No duplicates
        node->next = insertRecur(node->next, key, value);
        return node;
    }
    Node* removeRecur(Node* node, const K& key) {
        if (node == nullptr) return nullptr;
        if (node->key == key) {
            Node* temp = node;
            node = node->next;
            delete temp;
            return node;
            //Node* next = node->next;
            //delete node;
            //return next;
        }
        node->next = removeRecur(node->next, key);
        return node;
    }
};
