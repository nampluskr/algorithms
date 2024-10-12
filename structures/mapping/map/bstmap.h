#pragma once

template<typename K, typename V>
struct BSTMapRecur {
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
    };
    Node* root;

    BSTMapRecur() { root = nullptr; }
    ~BSTMapRecur() { clear(); }

    void clear() { clearRecur(root); root = nullptr; }
    // O(n)
    Node* find(const K& key) { return findRecur(root, key); }
    void emplace(const K& key, const V& value) { root = insertRecur(root, key, value); }
    void erase(const K& key) { root = removeRecur(root, key); }
    V& operator[](const K& key) {
        auto res = findRecur(root, key);
        if (res == nullptr) {
            emplace(key, {});
            res = findRecur(root, key);
        }
        return res->value;
    }

private:
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->left);
        clearRecur(node->right);
        delete node;
    }
    Node* findRecur(Node* node, const K& key) {
        if (node == nullptr) return nullptr;
        if (key == node->key) return node;
        else if (key < node->key) return findRecur(node->left, key);
        else return findRecur(node->right, key);
    }
    Node* insertRecur(Node* node, const K& key, const V& value) {
        if (node == nullptr) return new Node{ key, value, nullptr, nullptr };
        if (key == node->key) return node;    // No duplicates
        else if (key < node->key) node->left = insertRecur(node->left, key, value);
        else node->right = insertRecur(node->right, key, value);
        return node;
    }
    Node* removeRecur(Node* node, const K& key) {
        if (node == nullptr) return nullptr;
        if (node->key == key) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->right == nullptr) {
                Node* left = node->left;
                delete node;
                return left;
            } else if (node->left == nullptr) {
                Node* right = node->right;
                delete node;
                return right;
            } else {
                Node* minNode = findMin(node->right);
                node->key = minNode->key;
                node->right = removeRecur(node->right, node->key);
            }
        }
        if (key < node->key) node->left = removeRecur(node->left, key);
        else node->right = removeRecur(node->right, key);
        return node;
    }
    Node* findMin(Node* node) {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        else return findMin(node->left);
    }
};