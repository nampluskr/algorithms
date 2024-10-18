#pragma once
#include <cstdio>
#include <stack>

template<typename T>
struct SingleNode {
    T data;
    SingleNode* next;
};

template<typename T>
struct sll_list_recur {
    using Node = SingleNode<T>;
    Node* head;

    sll_list_recur() { head = nullptr; }
    ~sll_list_recur() { clear(); }

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
        return findRecur(node->next, data);
    }
    Node* insertRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates
        node->next = insertRecur(node->next, data);
        return node;
    }
    Node* removeRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            Node* next = node->next;
            delete node;
            return next;
        }
        node->next = removeRecur(node->next, data);
        return node;
    }
    void show() {
        printf(">> ");
        preOrder(head);
        printf("\n");
    }
    void preOrder(Node* node) {
        if (node == nullptr) return;
        printf("[%d]->", node->data);
        preOrder(node->next);
    }
};

template<typename T>
struct sll_list_iter {
    using Node = SingleNode<T>;
    Node* head;

    sll_list_iter() { head = nullptr; }
    ~sll_list_iter() { clear(); }

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
            curr = curr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return; // No duplicates
            prev = curr;
            curr = curr->next;
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
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return; // No data

        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
    void show() {
        printf(">> ");
        preOrder();
        printf("\n");
    }
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