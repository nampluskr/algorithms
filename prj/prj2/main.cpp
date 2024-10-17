#include "array_deque.h"
#include "linked_deque.h"
#include <cstdio>


template<typename T>
void testDeque(T& deq) {
    printf("\n");
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

    //printf(">> ");
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

    //printf(">> ");
    while (!deq.empty()) {
        auto data = deq.back(); deq.pop_back();
        printf("[%d] ", data);
    }
    printf("\n");

}

template<typename T>
void testStack(T& s) {
    printf("\n");
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

template<typename T>
void testQueue(T& q) {
    printf("\n");
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
    ArrayDeque<int> d1;
    LinkedDeque<int> d2;

    testDeque(d1);
    testDeque(d2);

    ArrayStack<int> s1;
    LinkedStack<int> s2;

    testStack(s1);
    testStack(s2);

    ArrayQueue<int> q1;
    LinkedQueue<int> q2;

    testQueue(q1);
    testQueue(q2);

    return 0;
}
