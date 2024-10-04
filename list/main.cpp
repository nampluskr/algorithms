#include "linked_list.h"

template<typename T>
void testList(T& sll) {
    sll.show();
    sll.insert(50);
    sll.insert(40);
    sll.insert(10);
    sll.insert(20);
    sll.insert(30);
    sll.insert(20);
    sll.show();

    sll.remove(30);
    sll.show();

    sll.clear();
    sll.show();
}

int main()
{
    UnorderedListRecur s1;
    UnorderedListIter s2;
    OrderedListRecur s3;
    OrderedListIter s4;

    testList(s1);
    testList(s2);
    testList(s3);
    testList(s4);


    return 0;
}