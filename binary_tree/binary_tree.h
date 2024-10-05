#pragma once
#include <cstdio>
#include <stack>
#include <queue>

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
};

struct BSTRecur {
    Node* root;

    BSTRecur() { root = nullptr; }
    ~BSTRecur() { clear(); }

    void clear() { clearRecur(root); root = nullptr; }
    Node* find(int data) { return findRecur(root, data); }
    void insert(int data) { root = insertRecur(root, data); }
    void remove(int data) { root = removeRecur(root, data); }
    void show() { printf(">> "); showRecur(root); printf("\n"); }

private:
    // void clearRecur(Node* node) {  // postorder traversal
    //     if (node == nullptr) return;
    // 
    //     clearRecur(node->left);
    //     clearRecur(node->right);
    //     delete node;
    // }
    void clearRecur(Node* node) {  // preorder traversal
        if (node == nullptr) return;

        Node* left = node->left;
        Node* right = node->right;
        delete node;

        clearRecur(left);
        clearRecur(right);
    }
    Node* findRecur(Node* node, int data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        if (data < node->data) return findRecur(node->left, data);
        else return findRecur(node->right, data);
    }
    Node* insertRecur(Node* node, int data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates allowed
        if (data < node->data) node->left = insertRecur(node->left, data);
        else node->right = insertRecur(node->right, data);
        return node;
    }
    Node* removeRecur(Node* node, int data) {
        // Implementation-1
        if (node == nullptr) return nullptr;
        if (node->data == data) {   // preorder
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

        // Implementation-2
        // if (node == nullptr) return nullptr;
        // if (data == node->data) {
        //     if (node->left == nullptr && node->right == nullptr) {
        //         delete node;
        //         return nullptr;
        //     } else if (node->right != nullptr) {
        //         Node* minNode = findMin(node->right);  // successor
        //         node->data = minNode->data;
        //         node->right = removeRecur(node->right, minNode->data);
        //     } else if (node->left != nullptr) {
        //         Node* maxNode = findMax(node->left);   // predecessor
        //         node->data = maxNode->data;
        //         node->left = removeRecur(node->left, maxNode->data);
        //     }
        // }
        // if (data < node->data) node->left = removeRecur(node->left, data);
        // else node->right = removeRecur(node->right, data);
        // return node;
    }
    void showRecur(Node* node) {
        if (node == nullptr) return;
        showRecur(node->left);
        printf("%d->", node->data); // inorder
        showRecur(node->right);
    }
    Node* findMin(Node* node) {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        else return findMin(node->left);
    }
    Node* findMax(Node* node) {
        if (node == nullptr) return nullptr;
        if (node->right == nullptr) return node;
        else return findMax(node->right);
    }
};

struct BSTIter {
    Node* root;

    BSTIter() { root = nullptr; }
    ~BSTIter() { clear(); }

    void clear() { // postorder traversal
        if (root == nullptr) return;

        std::stack<Node*> stack;
        stack.push(root);
        while (!stack.empty()) {
            Node* node = stack.top(); stack.pop();
            if (node->left != nullptr) stack.push(node->left);
            if (node->right != nullptr) stack.push(node->right);
            delete node;
        }
        root = nullptr;
    }
    Node* find(int data) {
        Node* node = root;
        while (node != nullptr) {
            if (node->data == data) return node;
            if (data < node->data) node = node->left;
            else node = node->right;
        }
        return nullptr;
    }
    void insert(int data) {
        Node* prev = nullptr;
        Node* node = root;
        while (node != nullptr) {
            if (node->data == data) return;  // No duplicates allowed
            prev = node;
            if (data < node->data) node = node->left;
            else node = node->right;
        }
        Node* newNode = new Node{ data, nullptr };
        if (prev == nullptr) root = newNode;
        else if (data < prev->data) prev->left = newNode;
        else prev->right = newNode;
    }
    void remove(int data) {
        Node* prev = nullptr;
        Node* node = root;
        while (node != nullptr) {
            if (node->data == data) break;
            prev = node;
            if (data < node->data) node = node->left;
            else node = node->right;
        }
        if (node == nullptr) return;

        if (node->left == nullptr && node->right == nullptr) {
            if (prev == nullptr) root = nullptr;
            else if (prev->left == node) prev->left = nullptr;
            else prev->right = nullptr;
        } else if (node->right == nullptr) {
            if (prev == nullptr) root = node->left;
            else if (prev->left == node) prev->left = node->left;
            else prev->right = node->left;
        } else if (node->left == nullptr) {
            if (prev == nullptr) root = node->right;
            else if (prev->left == node) prev->left = node->right;
            else prev->right = node->right;
        } else {    // 2 children
            Node* _prev = node;
            Node* _node = node->right;
            while (_node->left != nullptr) {
                _prev = _node;
                _node = _node->left;
            }
            node->data = _node->data;
            if (_prev->left == _node) _prev->left = _node->right;
            else _prev->right = _node->right;
            node = _node;
        }
        delete node;
    }
    void show() {   // inorder traversal
        printf(">> ");
        std::stack<Node*> S;
        Node* node = root;
        if (node == nullptr) { printf("\n"); return; }

        while (node != nullptr || !S.empty()) {
            while (node != nullptr) {
                S.push(node);
                node = node->left;
            }
            node = S.top(); S.pop();
            printf("%d->", node->data);
            node = node->right;
        }
        printf("\n");
    }
};