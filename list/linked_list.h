#pragma once
#include <cstdio>

struct Node {
    int data;
    Node* next;
};

struct UnorderedListRecur {
    Node* head;

    UnorderedListRecur() { head = nullptr; }
    ~UnorderedListRecur() { clear(); }

    void clear() { head = clearRecur(head); }
    Node* find(int data) { return findRecur(head, data); }
    void insert(int data) { head = insertRecur(head, data); }
    void remove(int data) { head = removeRecur(head, data); }
    void show() { printf(">> head->"); showRecur(head); printf("null\n"); }

    Node* clearRecur(Node* node) {
        if (node == nullptr) return nullptr;
        // Node* next = node->next;
        // delete node;
        // return clearRecur(next);
        clearRecur(node->next);
        delete node;
        return nullptr;
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
    void showRecur(Node* node) {
        if (node == nullptr) return;
        printf("%d->", node->data);
        showRecur(node->next);
    }
};

struct UnorderedListIter {
    Node* head;

    UnorderedListIter() { head = nullptr; }
    ~UnorderedListIter() { clear(); }

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
            if (node->data == data) {
                if (prev == nullptr) head = node->next;
                else prev->next = node->next;
                delete node;
                return;
            }
            prev = node;
            node = node->next;
        }
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

struct OrderedListRecur {
    Node* head;

    OrderedListRecur() { head = nullptr; }
    ~OrderedListRecur() { clear(); }

    void clear() { head = clearRecur(head); }
    Node* find(int data) { return findRecur(head, data); }
    void insert(int data) { head = insertRecur(head, data); }
    void remove(int data) { head = removeRecur(head, data); }
    void show() { printf(">> head->"); showRecur(head); printf("null\n"); }

    Node* clearRecur(Node* node) {
        if (node == nullptr) return nullptr;
        // Node* next = node->next;
        // delete node;
        // return clearRecur(next);
        clearRecur(node->next);
        delete node;
        return nullptr;
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
            if (node->data == data) {
                if (prev == nullptr) head = node->next;
                else prev->next = node->next;
                delete node;
                return;
            }
            if (node->data < data) { prev = node; node = node->next; }
            else return;
        }
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