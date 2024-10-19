#pragma once

template<typename T>
struct OrderedListPQ {
    struct Node { T data; Node* next; };
    Node* head;

    OrderedListPQ() { head = nullptr; }
    ~OrderedListPQ() { clear(); }

    void push(const T& data) { insert(data); }
    void pop() { Node* temp = head; head = head->next; delete temp; }
    bool empty() { return head == nullptr; }
    T top() { return head->data; }

    // Ordered Linked List (Iterative)
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