#pragma once
#include <cstdio>
#include <stack>
#include <queue>

// Recursive Traversals
template<typename T>
void preOrderRecur(const T* node) {
    if (node == nullptr) return;
    printf("[%d]->", node->data);
    preOrderRecur(node->left);
    preOrderRecur(node->right);
}

template<typename T>
void inOrderRecur(const T* node) {
    if (node == nullptr) return;
    inOrderRecur(node->left);
    printf("[%d]->", node->data);
    inOrderRecur(node->right);
}

template<typename T>
void postOrderRecur(const T* node) {
    if (node == nullptr) return;
    postOrderRecur(node->left);
    postOrderRecur(node->right);
    printf("[%d]->", node->data);
}


// Iterative Traversals
template<typename T>
void preOrder(const T* node) {
    if (node == nullptr) return;

    std::stack<T*> S;
    S.push(node);
    while (!S.empty()) {
        T* curr = S.top(); S.pop();

        printf("[%d]->", curr->data);
        if (curr->right != nullptr) S.push(curr->right);
        if (curr->left != nullptr) S.push(curr->left);
        // printf("[%d]->", curr->data);
    }
}

template<typename T>
void inOrded_stack(const T* node) {
    if (node == nullptr) return;

    std::stack<T*> S;
    T* curr = node;
    while (curr != nullptr || !S.empty()) {
        while (curr != nullptr) {
            S.push(curr);
            curr = curr->left;
        }
        curr = S.top(); S.pop();
        printf("[%d]->", curr->data);
        curr = curr->right;
    }
}

template<typename T>
void levelOrded_queue(const T* node) {
    if (node == nullptr) return;

    std::queue<T*> Q;
    Q.push(node);
    while (!Q.empty()) {
        T* curr = Q.front(); Q.pop();

        printf("[%d]->", curr->data);
        if (curr->right != nullptr) Q.push(curr->right);
        if (curr->left != nullptr) Q.push(curr->left);
        // printf("[%d]->", curr->data);
    }
}