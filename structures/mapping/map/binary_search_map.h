#pragma once

template<typename K, typename V>
struct BinarySearchMap {
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
    };
    Node* root;

    BinarySearchMap() { root = nullptr; }
    ~BinarySearchMap() { clear(); }

    void clear() { clearRecur(root); root = nullptr; }
    V* find(const K& key) {
        Node* res = findRecur(root, key);
        return (res == nullptr) ? nullptr : &res->value;
    }
    void emplace(const K& key, const V& value) { root = emplaceRecur(root, key, value); }
    void erase(const K& key) { root = eraseRecur(root, key); }
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
        clearRecur(node->left);
        clearRecur(node->right);
        delete node;
    }
    Node* findRecur(Node* node, const K& key) const {
        if (node == nullptr) return nullptr;
        if (key == node->key) return node;
        else if (key < node->key) return findRecur(node->left, key);
        else return findRecur(node->right, key);
    }
    Node* emplaceRecur(Node* node, const K& key, const V& value) {
        if (node == nullptr) return new Node{ key, value, nullptr, nullptr };
        if (key == node->key) { node->value = value; return node; }    // Update value
        else if (key < node->key) node->left = emplaceRecur(node->left, key, value);
        else node->right = emplaceRecur(node->right, key, value);
        return node;
    }
    Node* eraseRecur(Node* node, const K& key) {
        if (node == nullptr) return nullptr;
        if (node->key == key) {
            if (node->right == nullptr) {
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
                node->right = eraseRecur(node->right, node->key);
            }
        }
        if (key < node->key) node->left = eraseRecur(node->left, key);
        else node->right = eraseRecur(node->right, key);
        return node;
    }
    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        else return findMin(node->left);
    }
    Node* findMax(Node* node) const {
        if (node == nullptr) return nullptr;
        if (node->right == nullptr) return node;
        else return findMax(node->right);
    }
};