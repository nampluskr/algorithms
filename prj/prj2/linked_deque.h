#pragma once
#include <cstdio>

template<typename T>
struct LinkedDeque {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;

    LinkedDeque() { head = tail = nullptr; }
    ~LinkedDeque() { clear(); }

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    void pop_back() {
        Node* prev = nullptr;
        Node* curr = head;   // head != nullptr
        while (curr != tail) { prev = curr; curr = curr->next; }

        if (prev == nullptr) head = tail = nullptr;
        else { prev->next = nullptr; tail = prev; }
        delete curr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }

    T front() { return head->data; }
    T back() { return tail->data; }

    void show() {
        printf(">> ");
        Node* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
        printf("\n");
    }
};

template<typename T>
struct LinkedStack {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    LinkedStack() { head = nullptr; }
    ~LinkedStack() { clear(); }

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
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop(); }

    T top() { return head->data; }
};

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

    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop(); }
    T front() { return head->data; }
};
