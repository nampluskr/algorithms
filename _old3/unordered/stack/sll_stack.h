#pragma once

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct sll_stack {
    Node<T>* head;
    Node<T>* tail;

    sll_stack() { head = tail = nullptr; }
    ~sll_stack() { clear(); }

    // push_front
    void push(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head = newNode; }
    }
    // pop_front
    void pop() {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop(); }
    T top() { return head->data; }
};
