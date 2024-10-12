#pragma once

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
};

template<typename T>
struct bst_priority_queue {
    using Node = TreeNode<T>;
    Node* root;

    bst_priority_queue() { root = nullptr; }
    ~bst_priority_queue() { clear(); }

    // O(log n)
    void push(const T& data) {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return;    // No duplicates
            prev = curr;
            if (curr->data < data) curr = curr->left;
            else curr = curr->right;
        }
        Node* newNode = new Node{data, nullptr, nullptr};
        if (prev == nullptr) root = newNode;
        else if (prev->data < data) prev->left = newNode;
        else prev->right = newNode;
    }
    // O(log n): remove max node
    void pop(const T& data) {

    }
    Node* findMax(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }
    bool empty() { return root == nullptr; }
    // O(log n)
    T top() { return findMax(root)->data; }
};