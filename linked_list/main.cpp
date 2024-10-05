#include "linked_list.h"

template<typename T>
void testList(T& li) {
    li.show();
    li.insert(50);
    li.insert(40);
    li.insert(10);
    li.insert(20);
    li.insert(30);
    li.insert(20);
    li.show();

    li.remove(30);
    li.show();

    li.clear();
    li.show();
}

int main()
{
    UnorderedListRecur s1;
    UnorderedListIter s2;
    OrderedListRecur s3;
    OrderedListIter s4;

    testList(s1);
    // testList(s2);
    testList(s3);
    // testList(s4);

    return 0;
}