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
    ~sll_priority_queue() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    void push(const T& data) { head = pushRecur(head, data); }

    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;
    }
    Node* pushRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates
        else if (node->data < data) node = new Node{ data, node };
        else node->next = insertRecur(node->next, data);
        return node;
    }
    // pop_front
    void pop(const T& data) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    bool empty() { return head == nullptr; }
    T top() { return head->data; }
};