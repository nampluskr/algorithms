#pragma once
#include <cstdio>

template<typename T>
struct BinarySearchTree {
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    Node* root;

    BinarySearchTree() { root = nullptr; }
    ~BinarySearchTree() { clear(); }

    void clear() { clearRecur(root); root = nullptr; }
    T* find(const T& data) {
        Node* res = findRecur(root, data);
        return (res == nullptr) ? nullptr : &res->data;
    }
    void insert(const T& data) { root = insertRecur(root, data); }
    void remove(const T& data) { root = removeRecur(root, data); }

    // Priority queue:
    void push(const T& data) { insert(data); }
    void pop() { root = popRecur(root); }
    bool empty() { return root == nullptr; }
    T top() { return findMax(root)->data; }

    void show() { printf(">> "); inorder(root); printf("\n"); }
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        printf("[%d]->", node->data);
        inorder(node->right);
    }

    Node* popRecur(Node* node) {
        if (node == nullptr) return nullptr;

        if (node->right == nullptr) {
            //Node* temp = node;
            //node = node->left;
            //delete temp;
            //return node;
            Node* left = node->left;
            delete node;
            return left;
        }
        node->right = popRecur(node->right);
        return node;
    }

private:
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->left);
        clearRecur(node->right);
        delete node;
    }
    Node* findRecur(Node* node, const T& data) const {
        if (node == nullptr) return nullptr;
        if (data == node->data) return node;
        else if (data < node->data) return findRecur(node->left, data);
        else return findRecur(node->right, data);
    }
    Node* insertRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr, nullptr };
        if (data == node->data) return node;    // No duplicates
        else if (data < node->data) node->left = insertRecur(node->left, data);
        else node->right = insertRecur(node->right, data);
        return node;
    }
    Node* removeRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
                return node;
                //Node* left = node->left;
                //delete node;
                //return left;
            } else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
                return node;
                //Node* right = node->right;
                //delete node;
                //return right;
            } else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = removeRecur(node->right, node->data);
            }
        }
        if (data < node->data) node->left = removeRecur(node->left, data);
        else node->right = removeRecur(node->right, data);
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
