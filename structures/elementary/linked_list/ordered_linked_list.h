#pragma once
#include <stack>

template<typename T>
struct ordered_linked_list_iter {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    ordered_linked_list_iter() { head = nullptr; }
    ~ordered_linked_list_iter() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    T* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return &curr->data;
            if (data < curr->data) curr = curr->next;
            else break;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return; // No duplicates
            if (data < curr->data) { prev = curr; curr = curr->next; }
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
            if (data < curr->data) { prev = curr; curr = curr->next; }
            else return;    // No data
        }
        if (curr == nullptr) return; // No data
        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
};

template<typename T>
struct ordered_linked_list_recur {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    ordered_linked_list_recur() { head = nullptr; }
    ~ordered_linked_list_recur() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    T* find(const T& data) {
        Node* res = findRecur(head);
        return (res == nullptr)? nullptr : &res->data;
    }
    void insert(const T& data) { head = insertRecur(head, data); }
    void remove(const T& data) { head = removeRecur(head, data); }

private:
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;    // postorder
    }
    Node* findRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        if (data < node->data) return findRecur(node->next, data);
        else return nullptr;
    }
    Node* insertRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates
        if (data < node->data) node->next = insertRecur(node->next, data);
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
        if (data < node->data) node->next = removeRecur(node->next, data);
        else node = nullptr;    // No data
        return node;
    }
};