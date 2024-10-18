#pragma once
#include <cstdio>
#include <stack>

template<typename T>
struct SingleNode {
    T data;
    SingleNode* next;
};

template<typename T>
struct sll_set_recur {
    using Node = SingleNode<T>;
    Node* head;

    sll_set_recur() { head = nullptr; }
    ~sll_set_recur() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    Node* find(const T& data) { return findRecur(data); }
    void insert(const T& data) { head = insertRecur(head, data); }
    void remove(const T& data) { head = removeRecur(head, data); }

    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;
    }
    Node* findRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        else if (node->data < data) return findRecur(node->next, data);
        else return nullptr;
    }
    Node* insertRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates
        else if (node->data < data) node->next = insertRecur(node->next, data);
        else node = new Node{ data, node };
        return node;
    }
    Node* removeRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            Node* next = node->next;
            delete node;
            return next;
        }
        else if (node->data < data) node->next = removeRecur(node->next, data);
        else node = nullptr;
        return node;
    }
    void show() { printf(">> "); preOrder(head); printf("\n"); }
    void preOrder(Node* node) {
        if (node == nullptr) return;
        printf("[%d]->", node->data);
        preOrder(node->next);
    }
};

template<typename T>
struct sll_set_iter {
    using Node = SingleNode<T>;
    Node* head;

    sll_set_iter() { head = nullptr; }
    ~sll_set_iter() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    Node* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return curr;
            else if (curr->data < data) curr = curr->next;
            else break;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return; // No duplicates
            else if (curr->data < data) { prev = curr; curr = curr->next; }
            else break;
        }
        Node* newNode = new Node{ data, curr };
        if (prev == nullptr) head = newNode;
        else prev->next = newNode;
    }
    void remove(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) break;
            else if (curr->data < data) { prev = curr; curr = curr->next; }
            else return;
        }
        if (curr == nullptr) return; // No data

        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
    void show() { printf(">> "); preOrder(); printf("\n"); }
    void preOrder() {
        if (head == nullptr) return;

        std::stack<Node*> S;
        S.push(head);
        while (!S.empty()) {
            Node* node = S.top(); S.pop();
            if (node->next != nullptr) S.push(node->next);
            printf("[%d]->", node->data);
        }
    }
};