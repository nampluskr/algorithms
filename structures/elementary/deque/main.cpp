#include "array_deque.h"
#include "singly_linked_deque.h"
#include "doubly_linked_deque.h"
#include <cstdio>

template<typename T>
void testDeque(T& deq) {
    deq.clear();
    deq.push_front(10);
    deq.push_front(20);
    deq.push_front(30);
    deq.push_front(40);
    deq.push_front(50);
    deq.push_front(60);
    deq.push_front(70);
    deq.push_front(80);
    deq.push_front(90);

    printf(">> ");
    while (!deq.empty()) {
        auto data = deq.front(); deq.pop_front();
        printf("[%d] ", data);
    }
    printf("\n");

    deq.clear();
    deq.push_back(10);
    deq.push_back(20);
    deq.push_back(30);
    deq.push_back(40);
    deq.push_back(50);
    deq.push_back(60);
    deq.push_back(70);
    deq.push_back(80);
    deq.push_back(90);

    printf(">> ");
    while (!deq.empty()) {
        auto data = deq.back(); deq.pop_back();
        printf("[%d] ", data);
    }
    printf("\n");
}

int main()
{
    array_deque<int> d1;
    singly_linked_deque_head<int> d2;
    singly_linked_deque_head_tail<int> d3;
    circular_singly_linked_deque_tail<int> d4;
    doubly_linked_deque_head_tail<int> d5;
    circular_doubly_linked_deque_head<int> d6;

    printf("\n*** Array Deque:\n");
    testDeque(d1);

    printf("\n*** Singly Linked Deque (Head):\n");
    testDeque(d2);
    printf("\n*** Singly Linked Deque (Head / Tail):\n");
    testDeque(d3);
    printf("\n*** Circular Singly Linked Deque (Tail):\n");
    testDeque(d4);

    printf("\n*** Doubly Linked Deque (Head / Tail):\n");
    testDeque(d5);
    printf("\n*** Circular Doubly Linked Deque (Head):\n");
    testDeque(d6);


    return 0;
}