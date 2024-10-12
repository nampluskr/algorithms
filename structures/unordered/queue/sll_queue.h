#pragma once

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct sll_queue {
    Node<T>* head;
    Node<T>* tail;

    sll_queue() { head = tail = nullptr; }
    ~sll_queue() { clear(); }

    // pop_fton
    void pop() {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    // push_back
    void push(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop(); }
    T front() { return head->data; }
};
