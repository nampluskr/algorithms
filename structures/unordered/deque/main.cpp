#include "sll_deque.h"
#include "dll_deque.h"
#include "array_deque.h"
#include <cstdio>

template<typename T>
void testDeque(T& deq) {
    deq.push_front(30);
    deq.push_front(20);
    deq.push_front(10);
    deq.show();

    while (!deq.empty()) {
        deq.pop_front();
        deq.show();
    }

    deq.push_back(30);
    deq.push_back(20);
    deq.push_back(10);
    deq.show();

    while (!deq.empty()) {
        deq.pop_back();
        deq.show();
    }

    deq.push_front(20);
    deq.push_front(10);
    deq.push_back(30);
    deq.show();

    deq.clear();
    deq.show();
}


int main()
{
    sll_deque_head<int> d1;
    sll_deque_head_tail<int> d2;
    circular_sll_deque_tail<int> d3;
    dll_deque_head_tail<int> d4;
    circular_dll_deque_head<int> d5;
    array_deque<int> d6(4);

    // testDeque(d1);
    // testDeque(d2);
    // testDeque(d3);
    // testDeque(d4);
    // testDeque(d5);
    testDeque(d6);

    return 0;
}