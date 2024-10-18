#pragma once

template<typename T>
struct OrderedLinkedList {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    OrderedLinkedList() { head = nullptr; }
    ~OrderedLinkedList() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    T* find(const T& data) { 
        Node* res = findRecur(head, data);
        return (res == nullptr) ? nullptr : &res->data;
    }
    void insert(const T& data) { head = insertRecur(head, data); }
    void remove(const T& data) { head = removeRecur(head, data); }

    // Priority queue:
    void push(const T& data) { insert(data); }
    void pop() { Node* temp = head; head = head->next; delete temp; }
    bool empty() { return head == nullptr; }
    T top() { return head->data; }

    void show() {
        printf(">> ");
        Node* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
        printf("\n");
    }

private:
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;
    }
    Node* findRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        else if (data < node->data) return findRecur(node->next, data);
        else return nullptr;
    }
    Node* insertRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates
        else if (data < node->data) node->next = insertRecur(node->next, data);
        else node = new Node{ data, node };
        return node;
    }
    Node* removeRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            Node* temp = node;
            node = node->next;
            delete temp;
            return node;
            //Node* next = node->next;
            //delete node;
            //return next;
        }
        else if (data < node->data) node->next = removeRecur(node->next, data);
        else node = nullptr;
        return node;
    }
    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        return findMin(node->left);
    }
    Node* findMax(Node* node) const {
        return head;
    }
};
