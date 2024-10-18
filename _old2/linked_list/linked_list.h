#pragma once
#include <cstdio>
#include <stack>

struct Node {
    int data;
    Node* next;
};

struct LinkedListRecur {
    Node* head;

    LinkedListRecur() { head = nullptr; }
    ~LinkedListRecur() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    Node* find(int data) { return findRecur(head, data); }
    void insert(int data) { head = insertRecur(head, data); }
    void remove(int data) { head = removeRecur(head, data); }
    void show() { printf(">> head->"); preOrder(head); printf("null\n"); }

private:
    void clearRecur(Node* node) {
        // postorder
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;

        // preorder
        // if (node == nullptr) return;
        // Node* next = node->next;
        // delete node;
        // clearRecur(next);
    }
    Node* findRecur(Node* node, int data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        return findRecur(node->next, data);
    }
    Node* insertRecur(Node* node, int data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates allowed
        node->next = insertRecur(node->next, data);
        return node;
    }
    Node* removeRecur(Node* node, int data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            Node* next = node->next;
            delete node;
            return next;
        }
        node->next = removeRecur(node->next, data);
        return node;
    }
    void preOrder(Node* node) {
        if (node == nullptr) return;
        printf("%d->", node->data);
        preOrder(node->next);
    }
    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->next);
        printf("%d->", node->data);
    }
};


struct LinkedListIter {
    Node* head;

    LinkedListIter() { head = nullptr; }
    ~LinkedListIter() { clear(); }

    void clear() {
        // Node* node = head;
        // while (node != nullptr) {
        //     Node* next = node->next;
        //     delete node;
        //     node = next;
        // }
        // head = nullptr;

        // stack
        if (head == nullptr) return;
        std::stack<Node*> S;
        S.push(head);
        while (!S.empty()) {
            Node* node = S.top(); S.pop();
            if (node->next != nullptr) S.push(node->next);
            delete node;
        }
        head = nullptr;
    }
    Node* find(int data) {
        Node* node = head;
        while (node != nullptr) {
            if (node->data == data) return node;
            node = node->next;
        }
        return nullptr;
    }
    void insert(int data) {
        Node* prev = nullptr;
        Node* node = head;
        while (node != nullptr) {
            if (node->data == data) return; // No duplicates allowed
            prev = node;
            node = node->next;
        }
        Node* newNode = new Node{ data, node };
        if (prev == nullptr) head = newNode;
        else prev->next = newNode;
    }
    void remove(int data) {
        Node* prev = nullptr;
        Node* node = head;
        while (node != nullptr) {
            if (node->data == data) break;
            prev = node;
            node = node->next;
        }
        if (node == nullptr) return; // No data node

        if (prev == nullptr) head = node->next;
        else prev->next = node->next;
        delete node;
    }
    void show() { printf(">> head->"); preOrder(); printf("null\n"); }

private:
    void preOrder() {
        // Node* node = head;
        // while (node != nullptr) {
        //     printf("%d->", node->data);
        //     node = node->next;
        // }

        if (head == nullptr) return;

        std::stack<Node*> S;
        S.push(head);
        while (!S.empty()) {
            Node* node = S.top(); S.pop();
            if (node->next != nullptr) S.push(node->next);
            printf("%d->", node->data);
        }
    }
    void postOrder() {
        if (head == nullptr) return;

        std::stack<Node*> S;
        Node* node = head;
        while(node != nullptr) {
            S.push(node);
            node = node->next;
        }
        while (!S.empty()) {
            node = S.top(); S.pop();
            printf("%d->", node->data);
        }
    }
};


struct OrderedListRecur: LinkedListRecur {
    Node* head;

    OrderedListRecur() { head = nullptr; }
    ~OrderedListRecur() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    Node* find(int data) { return findRecur(head, data); }
    void insert(int data) { head = insertRecur(head, data); }
    void remove(int data) { head = removeRecur(head, data); }
    void show() { printf(">> head->"); showRecur(head); printf("null\n"); }

private:
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;
    }
    Node* findRecur(Node* node, int data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        else if (node->data < data) return findRecur(node->next, data);
        else return nullptr;
    }
    Node* insertRecur(Node* node, int data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates allowed
        if (node->data < data) node->next = insertRecur(node->next, data);
        else node = new Node{ data, node };
        return node;
    }
    Node* removeRecur(Node* node, int data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            Node* next = node->next;
            delete node;
            return next;
        }
        if (node->data < data) node->next = removeRecur(node->next, data);
        else node = nullptr;
        return node;
    }
    void showRecur(Node* node) {
        if (node == nullptr) return;
        printf("%d->", node->data);
        showRecur(node->next);
    }
};


struct OrderedListIter {
    Node* head;

    OrderedListIter() { head = nullptr; }
    ~OrderedListIter() { clear(); }

    void clear() {
        Node* node = head;
        while (node != nullptr) {
            Node* next = node->next;
            delete node;
            node = next;
        }
        head = nullptr;
    }
    Node* find(int data) {
        Node* node = head;
        while (node != nullptr) {
            if (node->data == data) return node;
            if (node->data < data) node = node->next;
            else return nullptr;
        }
        return nullptr;
    }
    void insert(int data) {
        Node* prev = nullptr;
        Node* node = head;
        while (node != nullptr) {
            if (node->data == data) return; // No duplicates allowed
            if (node->data < data) { prev = node; node = node->next; }
            else break;
        }
        Node* newNode = new Node{ data, node };
        if (prev == nullptr) head = newNode;
        else prev->next = newNode;
    }
    void remove(int data) {
        Node* prev = nullptr;
        Node* node = head;
        while (node != nullptr) {
            if (node->data == data) break;
            if (node->data < data) { prev = node; node = node->next; }
            else return;
        }
        if (node == nullptr) return;

        if (prev == nullptr) head = node->next;
        else prev->next = node->next;
        delete node;
    }
    void show() {
        printf(">> head->");
        Node* node = head;
        while (node != nullptr) {
            printf("%d->", node->data);
            node = node->next;
        }
        printf("null\n");
    }
};