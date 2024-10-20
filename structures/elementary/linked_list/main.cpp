#include "singly_linked_list.h"
#include "ordered_linked_list.h"
#include "linked_list_traversal.h"
#include <cstdio>

template<typename T>
void print(const T& lst) {
    printf(">> ");
    preOrder(lst.head);
    printf("\n");
}

template<typename T>
void testList(T& lst) {
    lst.insert(30);
    lst.insert(40);
    lst.insert(10);
    lst.insert(20);
    lst.insert(50);
    print(lst);

    lst.remove(50); print(lst);
    lst.remove(30); print(lst);
    lst.remove(20); print(lst);
    lst.remove(10); print(lst);
    lst.remove(40); print(lst);

    lst.insert(30);
    lst.insert(40);
    lst.insert(10);
    lst.insert(20);
    lst.insert(50);
    print(lst);

    lst.clear();
    print(lst);
}

int main()
{
    singly_linked_list_iter<int> l1;
    singly_linked_list_dummy<int> l2;
    singly_linked_list_recur<int> l3;
    ordered_linked_list_iter<int> l4;
    ordered_linked_list_recur<int> l5;

    printf("\n*** Singly Linked List (Iterative):\n");
    testList(l1);

    printf("\n*** Singly Linked List (Dummy Node):\n");
    testList(l2);

    printf("\n*** Singly Linked List (Recursive):\n");
    testList(l3);

    printf("\n*** Ordered Linked List (Iterative): Descending Order\n");
    testList(l4);

    printf("\n*** Ordered Linked List (Recursive): Descending Order\n");
    testList(l5);

    return 0;
}