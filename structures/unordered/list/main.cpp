#include "sll_list.h"
#include <cstdio>

template<typename T>
void testList(T& lst) {
    lst.insert(10);
    lst.insert(30);
    lst.insert(20);
    lst.show();

    lst.remove(30); lst.show();
    lst.remove(20); lst.show();
    lst.remove(10); lst.show();

    lst.insert(10);
    lst.insert(30);
    lst.insert(20);
    lst.show();

    lst.clear();
    lst.show();
}

int main()
{
    sll_list_recur<int> l1;
    sll_list_iter<int> l2;

    testList(l1);
    testList(l2);

    return 0;
}