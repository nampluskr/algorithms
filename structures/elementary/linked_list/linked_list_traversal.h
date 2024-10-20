#pragma once
#include <cstdio>

// Recursive Traversals
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


// Iterative Traversals
template<typename T>
void preOrder(T* node) {
    T* curr = node;
    while (curr != nullptr) {
        printf("[%d]->", curr->data);
        curr = curr->next;
    }
}