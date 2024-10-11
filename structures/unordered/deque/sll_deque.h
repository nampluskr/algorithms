#pragma once
#include "node.h"
#include <cstdio>

template<typename T>
struct sll_deque_head {
    using Node = SingleNode<T>;
    Node* head = nullptr;

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = newNode;
        else {
            Node* curr = head;
            while (curr->next != nullptr) curr = curr->next;
            curr->next = newNode;
        }
    }
    void pop_back() {
        Node* prev = nullptr;
        Node* curr = head;   // head != nullptr
        while (curr->next != nullptr) { prev = curr; curr = curr->next; }

        if (prev == nullptr) head = nullptr;
        else prev->next = nullptr;
        delete curr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> ");
        Node* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
        printf("\n");
    }
};

template<typename T>
struct sll_deque_head_tail {
    using Node = SingleNode<T>;
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    void pop_back() {
        Node* prev = nullptr;
        Node* curr = head;   // head != nullptr
        while (curr != tail) { prev = curr; curr = curr->next; }

        if (prev == nullptr) head = tail = nullptr;
        else { prev->next = nullptr; tail = prev; }
        delete curr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> ");
        Node* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
        printf("\n");
    }
};

template<typename T>
struct circular_sll_deque_tail {
    using Node = SingleNode<T>;
    Node* tail = nullptr;

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr };
        if (tail == nullptr) { tail = newNode; tail->next = tail; }
        else { newNode->next = tail->next; tail->next = newNode; }
    }
    void pop_front() {
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node* temp = tail->next;
            tail->next = temp->next;
            delete temp;
        }
    }
    void push_back(const T& data) {
        push_front(data);
        tail = tail->next;
    }
    void pop_back() {
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node* temp = tail;
            while (tail->next != temp) tail = tail->next;
            pop_front();
        }
    }
    bool empty() { return tail == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> ");
        if (tail != nullptr) {
            if (tail->next == tail) printf("[%d]->", tail->data);
            else {
                Node* curr = tail->next;
                while (curr != tail) {
                    printf("[%d]->", curr->data);
                    curr = curr->next;
                }
                printf("[%d]->", curr->data);
            }
        }
        printf("\n");
    }
};

