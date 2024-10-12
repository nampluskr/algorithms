# pragma once

template<typename T>
struct SingleNode {
    T data;
    SingleNode* next;
};

template<typename T>
struct sll_priority_queue {
    using Node = SingleNode<T>;
    Node* head;

    sll_priority_queue() { head = nullptr; }
    ~sll_priority_queue() { while (!empty()) pop(); }

    // O(n): insert (sll)
    void push(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return; // No duplicates
            else if (data < curr->data) { prev = curr; curr = curr->next; }
            else break;
        }
        Node* newNode = new Node{ data, curr };
        if (prev == nullptr) head = newNode;
        else prev->next = newNode;
    }
    // O(1): pop_front (sll)
    void pop() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) nullptr;
    }
    bool empty() { return head == nullptr; }
    // O(1)
    T top() { return head->data; }
};