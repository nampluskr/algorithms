#pragma once

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct sll_vector {
    Node<T>* head;
    Node<T>* tail;
    int cnt;

    sll_vector() { head = tail = nullptr; cnt = 0; }
    ~sll_vector() { clear(); }

    void clear() {
        Node<T>* node = head;
        while (node != nullptr) {
            Node<T>* temp = node;
            node = node->next;
            delete temp;
        }
        head = tail = nullptr; cnt = 0;
    }
    void push_back(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
        cnt++;
    }
    T front() { return head->data; }
    T back() { return tail->data; }
    bool empty() { return head == nullptr; }
    int size() { return cnt; }

    // for (int data: list) { data ... }
    // for (Iterator iter = begin(); iter != end(); iter++) { *iter ... }
    struct Iterator {
        Node<T>* ptr;
        Iterator(Node<T>* ptr) { this->ptr = ptr; }
        bool operator!=(const Iterator& iter) const { return ptr != iter.ptr; }
        T& operator*() {return ptr->data; }
        Iterator& operator++() { ptr = ptr->next; return *this; }   // prefix
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};