#pragma once

template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;

    LinkedList() { head = tail = nullptr; }
    ~LinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    Node* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    void remove(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return; // No data

        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }

    // for (Iterator iter = begin(); iter != end(); ++iter) { *iter }
    struct Iterator {
        Node* ptr;

        Iterator(Node* ptr = nullptr) { this->ptr = ptr; }
        bool operator!=(const Iterator& iter) const { return ptr != iter.ptr; }
        Iterator& operator++() { ptr = ptr->next; return *this; }
        T& operator*() { return ptr->data; }
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};
