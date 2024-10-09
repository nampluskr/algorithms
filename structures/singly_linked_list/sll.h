#pragma once

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct SLLHead {
    Node<T>* head = nullptr;

    void push_front(const T& data) {    // O(1)
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {                  // O(1)
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    void push_back(const T& data) {     // O(n)
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            prev = curr;
            curr = curr->next;
        }
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (prev == nullptr) head = newNode;
        else prev->next = newNode;
    }
    void pop_back() {                   // O(n)
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr->next != nullptr) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr) head = nullptr;
        else prev->next = nullptr;
        delete curr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
};

template<typename T>
struct SLLHeadTail {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    void push_front(const T& data) {    // O(1)
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {                  // O(1)
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    void push_back(const T& data) {     // O(1)
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    void pop_back() {                   // O(n)
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != tail) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr) head = tail = nullptr;
        else { tail = prev; prev->next = nullptr; }
        delete curr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
};

template<typename T>
struct CircularSLLTail {
    Node<T>* tail = nullptr;

    // O(1)
    void push_front(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (tail == nullptr) { newNode->next = newNode; tail = newNode; }
        else { newNode->next = tail->next; tail->next = newNode; }
    }
    // O(1)
    void pop_front() {
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        }
        else {
            Node<T>* temp = tail->next;
            tail->next = temp->next;
            delete temp;
        }
    }
    // O(1)
    void push_back(const T& data) {
        push_front(data);
        tail = tail->next;
    }
    // O(n)
    void pop_back() { 
        if (tail->next == tail) { // Empty or single node list
            delete tail;
            tail = nullptr;
        } else {
            Node<T>* prev = tail;
            Node<T>* curr = tail->next;
            while (curr != tail) {
                prev = curr;
                curr = curr->next;
            }
            prev->next = tail->next;
            delete tail;
            tail = prev;
    }
    }
    bool empty() { return tail == nullptr; }
    void clear() { while (!empty()) pop_front(); }
};