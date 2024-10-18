#include "singly_linked_list.h"
#include "ordered_linked_list.h"
#include <cstdio>

template<typename T>
void print(const T& lst) {
    printf(">> ");
    auto* curr = lst.head;
    while (curr != nullptr) {
        printf("[%d]->", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

template<typename T>
void testList(T& lst) {
    lst.insert(40);
    lst.insert(10);
    lst.insert(30);
    lst.insert(20);
    print(lst);

    lst.remove(30); print(lst);
    lst.remove(20); print(lst);
    lst.remove(10); print(lst);
    lst.remove(40); print(lst);

    lst.insert(40);
    lst.insert(10);
    lst.insert(30);
    lst.insert(20);
    print(lst);

    lst.clear();
    print(lst);
}

int main()
{
    singly_linked_list_iter<int> l1;
    singly_linked_list_recur<int> l2;
    ordered_linked_list_iter<int> l3;
    ordered_linked_list_recur<int> l4;

    printf("*** Singly Linked List:\n");
    testList(l1);
    testList(l2);

    printf("*** Ordered Linked List:\n");
    testList(l3);
    testList(l4);

    return 0;
}