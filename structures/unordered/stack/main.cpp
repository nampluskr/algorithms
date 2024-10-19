#include "array_stack.h"
#include "linked_stack.h"
#include <cstdio>

template<typename T>
void testStack(T& s) {
    s.clear();
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);

    printf(">> ");
    while (!s.empty()) {
        int data = s.top(); s.pop();
        printf("[%d]->", data);
    }
    printf("\n");
}

int main()
{
    ArrayStack<int> s1;
    LinkedStack<int> s2;

    printf("\n*** Linked Stack:\n");
    testStack(s1);

    printf("\n*** Array Stack:\n");
    testStack(s2);

    return 0;
}