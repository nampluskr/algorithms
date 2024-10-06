#pragma once

struct Node {
    int data;
    Node* next;
};

struct LinkedList {
    Node* head;
    Node* tail;
    int cnt;

    LinkedList() { head = tail = nullptr; cnt = 0; }
    ~LinkedList() { clear(); }

    void clear() {
        Node* node = head;
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
        head = tail = nullptr; cnt = 0;
    }
    void push_back(int data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
        cnt++;
    }
    int front() { return head->data; }
    int back() { return tail->data; }
    bool empty() { return head == nullptr; }
    int size() { return cnt; }

    // for (int data: list) { data ... }
    // for (Iterator iter = begin(); iter != end(); iter++) { *iter ... }
    struct Iterator {
        Node* ptr;
        Iterator(Node* ptr) { this->ptr = ptr; }
        bool operator!=(const Iterator& iter) const { return ptr != iter.ptr; }
        int& operator*() {return ptr->data; }
        Iterator& operator++() { ptr = ptr->next; return *this; }   // prefix
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

struct ArrayList {
    int* arr;
    int cnt;

    ArrayList(int maxSize=100) { arr = new int[maxSize]; cnt = 0; }
    ~ArrayList() { delete[] arr; }

    void clear() { cnt = 0; }
    void push_back(int data) { arr[cnt++] = data; }
    int front() { return arr[0]; }
    int back() { return arr[cnt - 1]; }
    bool empty() { return cnt == 0; }
    int size() { return cnt; }

    // int* begin() { return arr; }
    // int* end() { return arr + cnt; }

    struct Iterator {
        int* ptr;
        Iterator(int* p) : ptr(p) {}
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        int& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; } // prefix
    };
    Iterator begin() { return Iterator(arr); }
    Iterator end() { return Iterator(arr + cnt); }
};
