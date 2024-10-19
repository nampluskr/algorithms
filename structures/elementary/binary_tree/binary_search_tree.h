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
    // void clear() {
    //     if (root == nullptr) return;
 
    //     std::stack<Node*> S;
    //     S.push(root);
    //     while (!S.empty()) {
    //         Node* curr = S.top(); S.pop();
    //         if (curr->left != nullptr) S.push(curr->left);
    //         if (curr->right != nullptr) S.push(curr->right);
    //         delete curr;
    //     }
    //     root = nullptr;
    // }
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
    // Iterative (Variation-1)
    // void clear() {
    //     Node* curr = root;
    //     Node* prev = nullptr;
    //     while (curr != nullptr) {
    //         if (curr->left == nullptr) {
    //             // 왼쪽 자식이 없으면 현재 노드를 제거하고 오른쪽으로 이동
    //             Node* right = curr->right;
    //             delete curr;
    //             curr = right;
    //         } else { // 왼쪽 자식이 있는 동안 반복
    //             // 현재 노드의 왼쪽 자식을 가장 오른쪽 자식의 오른쪽으로 이동
    //             Node* temp = curr->left;
    //             while (temp->right != nullptr) temp = temp->right;
    //             temp->right = curr;

    //             // 왼쪽 서브트리로 이동
    //             Node* left = curr->left;
    //             curr->left = nullptr;
    //             prev = curr;
    //             curr = left;
    //         } 
    //     }
    //     root = nullptr;
    // }
    // Iterative (Variation-2)
    void clear() {
        Node* prev = nullptr;
        Node* curr = root;

        while (curr != nullptr) {
            if (curr->left == nullptr) {    // 왼쪽 자식이 없으면 오른쪽으로 이동
                Node* temp = curr;
                curr = curr->right;
                delete temp;
            } else {                        // 왼쪽 자식이 있을 경우 중위 선행자를 찾아야 함
                prev = curr->left;
                while (prev->right != nullptr && prev->right != curr) { 
                    prev = prev->right;
                }
                if (prev->right == nullptr) {   // 중위 선행자의 오른쪽을 현재 노드로 연결
                    prev->right = curr;
                    curr = curr->left;
                } else {                        // 중위 선행자의 오른쪽이 현재 노드로 연결된 경우
                    prev->right = nullptr;
                    Node* temp = curr;
                    curr = curr->right;
                    delete temp;
                }
            }
        }
        root = nullptr;
    }

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
    // preorder
    // void clearRecur(Node* node) {
    //     if (node == nullptr) return;
    //     Node* left = node->left;
    //     Node* right = node->right;
    //     delete node;        // preorder
    //     clearRecur(left);
    //     clearRecur(right);
    // }
    // inorder
    // void clearRecur(Node* node) {
    //     if (node == nullptr) return;
    //     clearRecur(node->left);
    //     Node* right = node->right;
    //     delete node;        // preorder
    //     clearRecur(right);
    // }
    // post order (Reference)
    // void clearRecur(Node* node) {
    //     if (node == nullptr) return;
    //     clearRecur(node->left);
    //     clearRecur(node->right);
    //     delete node;    // post order
    // }
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