#pragma once
#include <stack>
#include <cstdio>

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
};

template<typename T>
struct bst_set_recur {
    using Node = TreeNode<T>;
    Node* root;

    bst_set_recur() { root = nullptr; }
    ~bst_set_recur() { clear(); }

    void clear() { clearRecur(root); }
    Node* find(const T& data) { return findRecur(root, data); }
    void insert(const T& data) { root = insertRecur(root, data); }
    void remove(const T& data) { root = removeRecur(root, data); }

    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->left);
        clearRecur(node->right);
        delete node;
    }
    Node* findRecur(Node* node, const T& data) const {
        if (node == nullptr) return nullptr;
        if (data == node->data) return node;
        else if (data < node->data) return find(node->left, data);
        else return find(node->right, data);
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
    void show() { printf(">> "); inOrder(root); printf("\n"); }
    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        printf("[%d]->", node->data);
        inOrder(node->right);
    }
};

template<typename T>
struct bst_set_iter {
    using Node = TreeNode<T>;
    Node* root;

    bst_set_iter() { root = nullptr; }
    ~bst_set_iter() { clear(); }

    void clear() {
        if (root == nullptr) return;

        std::stack<Node*> S;
        S.push(root);
        while (!S.empty()) {
            Node* curr = S.top(); S.pop();
            if (curr->right) S.push(curr->right);
            if (curr->left) S.push(curr->left);
            delete curr;
        }
        root = nullptr;
    }
    Node* find(const T& data) {
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            else if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return;    // No duplicates
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        Node* newNode = new Node{data, nullptr, nullptr};
        if (prev == nullptr) root = newNode;
        else if (data < prev->data) prev->left = newNode;
        else prev->right = newNode;
    }
    void remove(const T& data) {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        if (curr == nullptr) return;   // No data

        if (curr->left == nullptr && curr->right == nullptr) {
            if (prev == nullptr) root = nullptr;
            else if (prev->left == curr) prev->left = nullptr;
            else prev->right = nullptr;
            delete curr;
            return;
        } else if (curr->left == nullptr) {
            if (prev == nullptr) root = curr->right;
            else if (prev->left == curr) prev->left = curr->right;
            else prev->right = curr->right;
        } else if (curr->right == nullptr) {
            if (prev == nullptr) root = curr->left;
            else if (prev->left == curr) prev->left = curr->left;
            else prev->right = curr->left;
        } else {
            Node* _prev = curr;
            Node* _curr = curr->right;
            while (_curr->left != nullptr) {
                _prev = _curr;
                _curr = _curr->left;
            }
            curr->data = _curr->data;
            if (_prev->left == _curr) _prev->left = _curr->right;
            else _prev->right = _curr->right;
            curr = _curr;
        }
        delete curr;
    }
    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }
    void show() { printf(">> "); inOrder(); printf("\n"); }
    void inOrder() const {
        if (root == nullptr) return;
        std::stack<Node*> S;
        Node* curr = root;
        while (curr != nullptr || !S.empty()) {
            while (curr != nullptr) {
                S.push(curr);
                curr = curr->left;
            }
            curr = S.top(); S.pop();
            printf("[%d]->", curr->data);
            curr = curr->right;
        }
    }
};