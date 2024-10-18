#pragma once
#include <cstdio>

// Recursive Traversals
template<typename T>
void inOrderRecur(T* node) {
    if (node == nullptr) return;
    inOrderRecur(node->left);
    printf("[%d]->", node->data);
    inOrderRecur(node->right);
}

template<typename T>
void preOrderRecur(T* node) {
    if (node == nullptr) return;
    printf("[%d]->", node->data);
    preOrderRecur(node->left);
    preOrderRecur(node->right);
}

template<typename T>
void postOrderRecur(T* node) {
    if (node == nullptr) return;
    postOrderRecur(node->left);
    postOrderRecur(node->right);
    printf("[%d]->", node->data);
}

// Iterative Traversals