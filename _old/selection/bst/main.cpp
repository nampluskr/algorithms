#include <cstdio>
#include "set_swea.h"
#include "..\data.h"
#include <vector>

Set<Data> s;
int cnt;

Set<Data>::Node* inorder(Set<Data>::Node* node, int k){
    if (node == NULL) return NULL;

    auto left = inorder(node->left, k);
    if(left != NULL) return left;
    if(++cnt == k) return node;

    return inorder(node->right, k);
}

void inorder(Set<Data>::Node* node) {
    if (node == nullptr) return;
    inorder(node->left);
    printf("(%d, %d) ", node->key.number, node->key.id);
    inorder(node->right);
}

void print() {
    printf(">> ");
    inorder(s.root);
    printf("\n");
}

int main()
{
    Data k1{ 111, 1 }, k2{ 222, 2}, k3{ 333, 3 }, k4{ 444, 4 }, k5{ 555, 5 };

    s.clear();
    s.insert(k3);
    s.insert(k2);
    s.insert(k1);
    s.insert(k5);
    s.insert(k4);
    print();

    cnt = 0;
    auto kth = inorder(s.root, 5);

    s.clear();
    print();

    return 0;
}