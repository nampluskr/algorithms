#pragma once

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
};

template<typename T>
struct bst_priority_queue_recur {
    using Node = TreeNode<T>;
    Node* root;

    bst_priority_queue_recur() { root = nullptr; }
    ~bst_priority_queue_recur() { while (!empty()) pop(); }

    void push(const T& data) { root = pushRecur(root, data); }
    void pop() { root = popRecur(root); }
    bool empty() { return root == nullptr; }
    T top() { return findMax(root)->data; }

    // O(log n): insert (bst)
    Node* pushRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr, nullptr };
        if (data == node->data) return node;    // No duplicates
        else if (node->data < data) node->left = pushRecur(node->left, data);
        else node->right = pushRecur(node->right, data);
        return node;
    }
    // O(log n): remove max node
    Node* popRecur(Node* node) {
        if (node == nullptr) return nullptr;

        if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
            return node;
        }
        node->left = popRecur(node->left);
        return node;
    }
    Node* findMax(Node* node) const {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        else return findMax(node->left);
    }
};

template<typename T>
struct bst_priority_queue_iter {
    using Node = TreeNode<T>;
    Node* root;

    bst_priority_queue_iter() { root = nullptr; }
    ~bst_priority_queue_iter() { while (!empty()) pop(); }

    bool empty() { return root == nullptr; }
    T top() { return findMax(root)->data; }

    // O(log n): insert (bst)
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
    void pop() {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr->left != nullptr) {
            prev = curr;
            curr = curr->left;
        }
        if (prev == nullptr) root = curr->right;
        else prev->left = curr->right;
        delete curr;
    }
    Node* findMax(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }
};