# pragma once

template<typename T>
struct SingleNode {
    T data;
    SingleNode* next;
};

template<typename T>
struct sll_priority_queue_recur {
    using Node = SingleNode<T>;
    Node* head;

    sll_priority_queue_recur() { head = nullptr; }
    ~sll_priority_queue_recur() { while (!empty()) pop(); }

    void push(const T& data) { head = pushRecur(head, data); }

    // O(n): insert (sll)
    Node* pushRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node; // No duplicates
        else if (data < node->data) node->next = pushRecur(node->next, data);
        else node = new Node{ data, node };
        return node;
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

template<typename T>
struct sll_priority_queue_iter {
    using Node = SingleNode<T>;
    Node* head;

    sll_priority_queue_iter() { head = nullptr; }
    ~sll_priority_queue_iter() { while (!empty()) pop(); }

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