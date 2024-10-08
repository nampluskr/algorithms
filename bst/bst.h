#pragma once
#include <cstdio>
#include <stack>

struct Node {
    int data;
    Node* left;
    Node* right;
};

// BST Interface
struct BSTInterface {
    virtual ~BSTInterface() {}

    virtual void clear(Node* node) = 0;
    virtual Node* find(Node* node, int data) const = 0;
    virtual Node* insert(Node* node, int data) = 0;
    virtual Node* remove(Node* node, int data) = 0;
    virtual Node* findMin(Node* node) const = 0;
    virtual void inOrder(Node* node) const = 0;
};

// Concrete BST
struct BSTRecur: BSTInterface {
    void clear(Node* node) override {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    Node* find(Node* node, int data) const override {
        if (node == nullptr) return nullptr;
        if (data == node->data) return node;
        else if (data < node->data) return find(node->left, data);
        else return find(node->right, data);
    }
    Node* insert(Node* node, int data) override {
        if (node == nullptr) return new Node{ data, nullptr, nullptr };
        if (data == node->data) return node;    // No duplicates
        else if (data < node->data) node->left = insert(node->left, data);
        else node->right = insert(node->right, data);
        return node;
    }
    Node* remove(Node* node, int data) override {
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
                node->right = remove(node->right, node->data);
            }
        }
        if (data < node->data) node->left = remove(node->left, data);
        else node->right = remove(node->right, data);
        return node;
    }
    Node* findMin(Node* node) const override {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        else return findMin(node->left);
    }
    void inOrder(Node* node) const override {
        if (node == nullptr) return;
        inOrder(node->left);
        printf("[%d]->", node->data);
        inOrder(node->right);
    }
};

// Concrete BST
struct BSTIter: BSTInterface {
    void clear(Node* node) override {
        if (node == nullptr) return;

        std::stack<Node*> S;
        S.push(node);
        while (!S.empty()) {
            Node* curr = S.top(); S.pop();
            if (curr->right) S.push(curr->right);
            if (curr->left) S.push(curr->left);
            delete curr;
        }
    }
    Node* find(Node* node, int data) const override {
        Node* curr = node;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            else if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }
    Node* insert(Node* node, int data) override {
        Node* prev = nullptr;
        Node* curr = node;
        while (curr != nullptr) {
            if (data == curr->data) return node;    // No duplicates
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        Node* newNode = new Node{data, nullptr, nullptr};
        if (prev == nullptr) return newNode;
        else if (data < prev->data) prev->left = newNode;
        else prev->right = newNode;
        return node;
    }
    Node* remove(Node* node, int data) override {
        Node* prev = nullptr;
        Node* curr = node;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        if (curr == nullptr) return node;

        if (curr->left == nullptr && curr->right == nullptr) {
            if (prev == nullptr) node = nullptr;
            else if (prev->left == curr) prev->left = nullptr;
            else prev->right = nullptr;
            delete curr;
            return node;
        }
        else if (curr->left == nullptr) {
            if (prev == nullptr) node = curr->right;
            else if (prev->left == curr) prev->left = curr->right;
            else prev->right = curr->right;
        } else if (curr->right == nullptr) {
            if (prev == nullptr) node = curr->left;
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
        return node;
    }
    Node* findMin(Node* node) const override {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }
    void inOrder(Node* node) const override {
        if (node == nullptr) return;
        std::stack<Node*> S;
        Node* curr = node;
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

// Client BST
struct BinarySearchTree {
    BSTInterface* bst;
    Node* root;

    BinarySearchTree(BSTInterface* bst) { this->bst = bst, root = nullptr; }

    void clear() { bst->clear(root); root = nullptr; }
    Node* find(int data) { return bst->find(root, data); }
    void insert(int data) { root = bst->insert(root, data); }
    void remove(int data) { root = bst->remove(root, data); }
    void show() { printf(">> "); bst->inOrder(root); printf("\n"); }
};

#if 0
void clear() {
        // 루트 노드부터 시작하여 후위 순회하며 삭제
        Node* current = root;
        Node* temp;
        while (current) {
            if (current->left) {
                // 왼쪽 자식이 있으면 왼쪽 서브트리로 이동
                current = current->left;
            } else {
                // 왼쪽 자식이 없으면 오른쪽 자식 또는 부모 노드로 이동
                temp = current;
                if (current->right) {
                    current = current->right;
                } else {
                    // 현재 노드를 삭제하고 부모 노드의 포인터를 null로 설정
                    if (temp == root) {
                        root = nullptr;
                    } else if (temp == temp->parent->left) {
                        temp->parent->left = nullptr;
                    } else {
                        temp->parent->right = nullptr;
                    }
                    delete temp;
                    current = nullptr;
                }
            }
        }
    }
#endif

#if 0
// 중위 순회: 위 코드는 중위 순회를 기반으로 구현되었습니다.
// 전위 순회나 후위 순회를 위해서는 스택의 사용 방식을 변경해야 합니다.
// 시간 복잡도: 중위 순회의 시간 복잡도는 O(n)입니다.
// 메모리 공간: 스택을 사용하기 때문에 추가적인 메모리 공간이 필요합니다.
    struct Iterator {
        Node* current;
        std::stack<Node*> stack;

        Iterator(Node* root) {
            current = root;
            while (current) {
                stack.push(current);
                current = current->left;
            }
        }

        bool operator!=(const Iterator& other) const {
            return stack != other.stack;
        }

        Iterator& operator++() {
            current = stack.top();
            stack.pop();

            Node* next = current->right;
            while (next) {
                stack.push(next);
                next = next->left;
            }

            return *this;
        }

        int& operator*() {
            return current->data;
        }
    };

    Iterator begin() { return Iterator(root); }
    Iterator end() { return Iterator(nullptr); }
#endif