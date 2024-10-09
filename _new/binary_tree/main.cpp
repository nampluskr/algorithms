#include "binary_tree.h"

template<typename T>
void testList(T& li) {
    li.clear(); li.show();

    li.insert(20);
    li.insert(50);
    li.insert(40);
    li.insert(10);
    li.insert(30);
    li.insert(20);
    li.show();

    li.remove(20); li.show();
    li.remove(30); li.show();
    li.remove(10); li.show();
    li.remove(50); li.show();

    li.clear(); li.show();
}

int main()
{
    BSTRecur b1;
    BSTIter b2;

    testList(b1);
    testList(b2);


    return 0;
}