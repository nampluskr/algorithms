#pragma once

template<typename T>
struct LinkedQueue {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;

    LinkedQueue() { head = tail = nullptr; }
    ~LinkedQueue() { clear(); }

    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop(); }
    T front() { return head->data; }

    // pop_front
    void pop() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    // push_back
    void push(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
};