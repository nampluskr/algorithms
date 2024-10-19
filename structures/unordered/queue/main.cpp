#include "array_queue.h"
#include "linked_queue.h"
#include <cstdio>

template<typename T>
void testQueue(T& q) {
    q.clear();
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    printf(">> ");
    while (!q.empty()) {
        int data = q.front(); q.pop();
        printf("[%d]->", data);
    }
    printf("\n");
}

int main()
{
    ArrayQueue<int> q1;
    LinkedQueue<int> q2;

    printf("\n*** Linked Queue:\n");
    testQueue(q1);

    printf("\n*** Array Queue:\n");
    testQueue(q2);

    return 0;
}