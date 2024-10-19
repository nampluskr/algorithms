#pragma once

template<typename T>
struct singly_linked_deque_head {
    struct Node { T data; Node* next; };
    Node* head;

    singly_linked_deque_head() { head = nullptr; }
    ~singly_linked_deque_head() { clear(); }

    void clear() { while (!empty()) pop_front(); }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    T back() {
        Node* curr = head;
        while (curr->next != nullptr) curr = curr->next;
        return curr->data;
    }

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = newNode;
        else {
            Node* curr = head;
            while (curr->next != nullptr) curr = curr->next;
            curr->next = newNode;
        }
    }
    void pop_back() {
        Node* prev = nullptr;
        Node* curr = head;   // head != nullptr
        while (curr->next != nullptr) { prev = curr; curr = curr->next; }

        if (prev == nullptr) head = nullptr;
        else prev->next = nullptr;
        delete curr;
    }
};

template<typename T>
struct singly_linked_deque_head_tail {
    struct Node { T data; Node* next; };
    Node* head;
    Node* tail;

    singly_linked_deque_head_tail() { head = tail = nullptr; }
    ~singly_linked_deque_head_tail() { clear(); }

    void clear() { while (!empty()) pop_front(); }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    T back() { return tail->data; }

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
};

template<typename T>
struct circular_singly_linked_deque_tail {
    struct Node { T data; Node* next; };
    Node* tail;

    circular_singly_linked_deque_tail() { tail = nullptr; }
    ~circular_singly_linked_deque_tail() { clear(); }

    void clear() { while (!empty()) pop_front(); }
    bool empty() { return tail == nullptr; }
    T front() { return tail->next->data; }
    T back() { return tail->data; }

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (tail == nullptr) { tail = newNode; tail->next = tail; }
        else { newNode->next = tail->next; tail->next = newNode; }
    }
    void pop_front() {
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node* temp = tail->next;
            tail->next = temp->next;
            delete temp;
        }
    }
    void push_back(const T& data) {
        push_front(data);
        tail = tail->next;
    }
    void pop_back() {
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node* temp = tail;
            while (tail->next != temp) tail = tail->next;
            pop_front();
        }
    }
};