#pragma once
#include "node.h"
#include <cstdio>

template<typename T>
struct dll_deque_head_tail {
    using Node = DoubleNode<T>;
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head->prev = newNode; head = newNode; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        else head->prev = nullptr;
        delete temp;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->prev = tail; tail->next = newNode; tail = newNode; }
    }
    void pop_back() {
        Node* temp = tail;
        tail = tail->prev;
        if (tail == nullptr) head = nullptr;
        else tail->next = nullptr;
        delete temp;
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
struct circular_dll_deque_head {
    using Node = DoubleNode<T>;
    Node* head;

    circular_dll_deque_head() { head = nullptr; }
    ~circular_dll_deque_head() { clear(); }

    void push_front(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) {
            newNode->prev = newNode->next = newNode;
            head = newNode;
        } else {
            Node* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = head->prev = newNode;
            head = newNode;
        }
    }
    void pop_front() {
        Node* temp = head;
        if (head == head->prev) head = nullptr;
        else {
            Node* tail = head->prev;
            head = head->next;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
    }
    void push_back(const T& data) {
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (head == nullptr) {
            newNode->prev = newNode->next = newNode;
            head = newNode;
        } else {
            Node* tail = head->prev;
            newNode->next = head;
            head->prev = newNode;
            newNode->prev = tail;
            tail->next = newNode;
        }
    }
    void pop_back() {
        Node* temp = head->prev;
        if (head == head->prev) head = nullptr;
        else {
            Node* tail = head->prev->prev;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> ");
        if (head != nullptr) {
            if (head->next == head) printf("[%d]->", head->data);
            else {
                Node* curr = head;
                while (curr->next != head) {
                    printf("[%d]->", curr->data);
                    curr = curr->next;
                }
                printf("[%d]->", curr->data);
            }
        }
        printf("\n");
    }
};