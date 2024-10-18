#include "binary_search_tree.h"
#include "binary_tree_traversal.h"
#include <cstdio>

template<typename T>
void print(const T& bst) {
    printf(">> ");
    inOrderRecur(bst.root);
    printf("\n");
}

template<typename T>
void testTree(T& bst) {
    bst.insert(30);
    bst.insert(40);
    bst.insert(10);
    bst.insert(20);
    bst.insert(50);
    print(bst);

    bst.remove(50); print(bst);
    bst.remove(30); print(bst);
    bst.remove(20); print(bst);
    bst.remove(10); print(bst);
    bst.remove(40); print(bst);

    bst.insert(30);
    bst.insert(40);
    bst.insert(10);
    bst.insert(20);
    bst.insert(50);
    print(bst);

    bst.clear();
    print(bst);
}

int main()
{
    binary_search_tree_iter<int> t1;
    binary_search_tree_recur<int> t2;

    printf("\n*** Binary Search Tree (Iterative):\n");
    testTree(t1);

    printf("\n*** Binary Search Tree (Recursive):\n");
    testTree(t2);

    return 0;
}