#pragma once
#include <cstdio>

template<typename T>
void preOrderRecur(T* node) {
    if (node == nullptr) return;
    printf("[%d]->", node->data);
    preOrderRecur(node->next);
}

template<typename T>
void postOrderRecur(T* node) {
    if (node == nullptr) return;
    postOrderRecur(node->next);
    printf("[%d]->", node->data);
}

template<typename T>
void preOrder(T* node) {
    T* curr = node;
    while (curr != nullptr) {
        printf("[%d]->", curr->data);
        curr = curr->next;
    }
}