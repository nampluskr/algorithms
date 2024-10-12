#include <set>
#include "bst_set.h"
#include "sll_set.h"
#include <cstdio>

template<typename T>
void testMap(T& set) {
    set.insert(30);
    set.insert(50);
    set.insert(30);
    set.insert(20);
    set.insert(10);
    set.insert(40);
    set.show();

    set.remove(30); set.show();
    set.remove(20); set.show();
    set.remove(40); set.show();
    set.remove(10); set.show();
    set.remove(50); set.show();
}

int main()
{
    bst_set_recur<int> s1;
    bst_set_iter<int> s2;
    sll_set_recur<int> s3;
    sll_set_iter<int> s4;

    testMap(s1);
    testMap(s2);
    testMap(s3);
    testMap(s4);

    return 0;
}