#include "linked_list.h"
#include "array_list.h"
#include <cstdio>

template<typename T>
void testList(T& lst) {
    lst.clear();
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    lst.push_back(50);
    lst.push_back(60);
    lst.push_back(70);
    lst.push_back(80);
    lst.push_back(90);

    printf(">> ");
    for (auto data : lst) printf("[%d]->", data);
    printf("\n");

    printf(">> ");
    while (!lst.empty()) {
        auto data = lst.back(); lst.pop_back();
        printf("[%d]->", data);
    }
    printf("\n");
}

int main()
{
    LinkedList<int> l1;
    ArrayList<int> l2;

    printf("\n*** Linked List:\n");
    testList(l1);

    printf("\n*** Array List:\n");
    testList(l2);

    return 0;
}