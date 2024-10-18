#pragma once
#include <stack>
#include <queue>

template<typename T>
struct binary_search_tree_iter {
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    Node* root;

    binary_search_tree_iter() { root = nullptr; }
    ~binary_search_tree_iter() { clear(); }

    // preorder
    void clear() {
        if (root == nullptr) return;
 
        std::stack<Node*> S;
        S.push(root);
        while (!S.empty()) {
            Node* curr = S.top(); S.pop();
            if (curr->left != nullptr) S.push(curr->left);
            if (curr->right != nullptr) S.push(curr->right);
            delete curr;
        }
        root = nullptr;
    }
    // level order
    // void clear() {
    //     if (root == nullptr) return;

    //     std::queue<Node*> Q;
    //     Q.push(root);
    //     while (!Q.empty()) {
    //         auto curr = Q.front(); Q.pop();
    //         if (curr->left != nullptr) Q.push(curr->left);
    //         if (curr->right != nullptr) Q.push(curr->right);
    //         delete curr;
    //     }
    //     root = nullptr;
    // }
    T* find(const T& data) {
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return;     // No duplicates
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else if (curr->data < data) curr = curr->right;
        }
        Node* node = new Node{ data, nullptr };
        if (prev == nullptr) root = node;
        else if (data < prev->data) prev->left = node;
        else prev->right = node;
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
        if (curr == nullptr) return;    // No data

        // if (curr->left == nullptr && curr->right == nullptr) {
        //     if (prev == nullptr) root = nullptr;
        //     else if (data < prev->data) prev->left = nullptr;
        //     else prev->right = nullptr;
        // }
        if (curr->right == nullptr) {
            if (prev == nullptr) root = curr->left;
            else if (data < prev->data) prev->left = curr->left;
            else prev->right = curr->left;
        }
        else if (curr->left == nullptr) {
            if (prev == nullptr) root = curr->right;
            else if (data < prev->data) prev->left = curr->right;
            else prev->right = curr->right;
        }
        else {
            Node* succ_prev = curr;
            Node* succ_curr = curr->right;
            while (succ_curr->left != nullptr) {
                succ_prev = succ_curr;
                succ_curr = succ_curr->left;
            }
            curr->data = succ_curr->data;
            if (succ_prev->left == succ_curr) succ_prev->left = succ_curr->right;
            else succ_prev->right = succ_curr->right;
            curr = succ_curr;    // delete successor
        }
        delete curr;
    }

private:
    Node* findMin(Node* curr) {
        if (curr == nullptr) return nullptr;
        while (curr->left != nullptr) curr = curr->left;
        return curr;
    }
    Node* findMax(Node* curr) {
        if (curr == nullptr) return nullptr;
        while (curr->right != nullptr) curr = curr->right;
        return curr;
    }
};


template<typename T>
struct binary_search_tree_recur {
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    Node* root;

    binary_search_tree_recur() { root = nullptr; }
    ~binary_search_tree_recur() { clear(); }

    void clear() { clearRecur(root); root = nullptr; }
    T* find(const T& data) {
        Node* res = findRecur(root, data);
        return (res == nullptr) ? nullptr : &res->data;
    }
    void insert(const T& data) { root = insertRecur(root, data); }
    void remove(const T& data) { root = removeRecur(root, data); }

private:
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->left);
        clearRecur(node->right);
        delete node;    // post order
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
    // Variation-1 (Reference)
    Node* removeRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            // if (node->left == nullptr && node->right == nullptr) {
            //     delete node;
            //     return nullptr;
            // }
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
                node->data = minNode->data;
                node->right = removeRecur(node->right, node->data);
            }
        }
        if (data < node->data) node->left = removeRecur(node->left, data);
        else node->right = removeRecur(node->right, data);
        return node;
    }
    // Variation-2
    // Node* removeRecur(Node* node, const T& data) {
    //     if (node == nullptr) return nullptr;
    //     if (node->data == data) {
    //         // if (node->left == nullptr && node->right == nullptr) {
    //         //     delete node;
    //         //     return nullptr;
    //         // }
    //         if (node->right == nullptr) {
    //             Node* temp = node;
    //             node = node->left;
    //             delete temp;
    //             return node;
    //         } else if (node->left == nullptr) {
    //             Node* temp = node;
    //             node = node->right;
    //             delete temp;
    //             return node;
    //         } else {
    //             Node* minNode = findMin(node->right);
    //             node->data = minNode->data;
    //             node->right = removeRecur(node->right, node->data);
    //         }
    //     }
    //     if (data < node->data) node->left = removeRecur(node->left, data);
    //     else node->right = removeRecur(node->right, data);
    //     return node;
    // }
    // Variation-3
    // Node* removeRecur(Node* node, const T& data) {
    //     if (node == nullptr) return nullptr;
    //     if (node->data == data) {
    //         if (node->left == nullptr && node->right == nullptr) {
    //             delete node;
    //             return nullptr;
    //         }
    //         else if (node->right != nullptr) {
    //             Node* minNode = findMin(node->right);   // successor
    //             node->data = minNode->data;
    //             node->right = removeRecur(node->right, minNode->data);
    //         }
    //         else if (node->left != nullptr) {
    //             Node* maxNode = findMax(node->left);    // predecessor
    //             node->data = maxNode->data;
    //             node->left = removeRecur(node->left, maxNode->data);
    //         }
    //         return node;
    //     }
    //     if (data < node->data) node->left = removeRecur(node->left, data);
    //     else node->right = removeRecur(node->right, data);
    //     return node;
    // }
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