#pragma once

template<typename T>
struct LinkedStack {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    LinkedStack() { head = nullptr; }
    ~LinkedStack() { clear(); }

    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop(); }
    T top() { return head->data; }

    // push_front
    void push(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = newNode;
        else { newNode->next = head; head = newNode; }
    }
    // pop_front
    void pop() {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
};