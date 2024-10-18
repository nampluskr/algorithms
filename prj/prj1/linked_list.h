#pragma once


template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    int listSize;

    LinkedList() { head = nullptr; listSize = 0; }
    ~LinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }
    bool empty() { return head == nullptr; }
    int size() { return listSize; }
    T back() { return head->data; }

    void push_back(const T& data) {
        head = new Node{ data, head };
        listSize++;
    }
    void pop_back() {
        Node* temp = head;
        head = head->next;
        delete temp;
        listSize--;
    }
    T* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return &curr->data;
            curr = curr->next;
        }
        return nullptr;
    }
    void remove(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) break;
            curr = curr->next;
        }
        if (curr == nullptr) return;    // No data
        if (prev == nullptr) head = nullptr;
        else prev->next = curr->next;
        delete curr;
        listSize--;
    }

    struct Iterator {
        Node* ptr;

        Iterator(Node* ptr) { this->ptr = ptr; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return !(ptr == other.ptr); }
        Iterator operator++() { ptr = ptr->next; return *this; }
        T& operator*() { return ptr->data; }
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};
