#pragma once

template<typename T>
struct doubly_linked_deque_head_tail {
    struct Node { T data; Node* prev; Node* next; };
    Node* head;
    Node* tail;

    doubly_linked_deque_head_tail() { head = tail = nullptr; }
    ~doubly_linked_deque_head_tail() { clear(); }

    void clear() { while (!empty()) pop_front(); }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    T back() { return tail->data; }

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head->prev = newNode; head = newNode; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        else head->prev = nullptr;
        delete temp;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->prev = tail; tail->next = newNode; tail = newNode; }
    }
    void pop_back() {
        Node* temp = tail;
        tail = tail->prev;
        if (tail == nullptr) head = nullptr;
        else tail->next = nullptr;
        delete temp;
    }
};

template<typename T>
struct circular_doubly_linked_deque_head {
    struct Node { T data; Node* prev; Node* next; };
    Node* head;

    circular_doubly_linked_deque_head() { head = nullptr; }
    ~circular_doubly_linked_deque_head() { clear(); }

    void clear() { while (!empty()) pop_front(); }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    T back() { return head->prev->data; }

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) {
            newNode->prev = newNode->next = newNode;
            head = newNode;
        } else {
            Node* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = head->prev = newNode;
            head = newNode;
        }
    }
    void pop_front() {
        Node* temp = head;
        if (head == head->prev) head = nullptr;
        else {
            Node* tail = head->prev;
            head = head->next;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) {
            newNode->prev = newNode->next = newNode;
            head = newNode;
        } else {
            Node* tail = head->prev;
            newNode->next = head;
            head->prev = newNode;
            newNode->prev = tail;
            tail->next = newNode;
        }
    }
    void pop_back() {
        Node* temp = head->prev;
        if (head == head->prev) head = nullptr;
        else {
            Node* tail = head->prev->prev;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
    }
};

