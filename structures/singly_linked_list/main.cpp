#include "sll.h"
#include <cstdio>

template<typename T>
void show(const T& deq) {
    printf(">> head->");
    // auto curr = deq.head;
    if (deq.tail != nullptr) {
        auto curr = deq.tail->next;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
    }
    printf("null\n");
}

template<typename T>
void testDeque(T& deq) {
    deq.push_front(30);
    deq.push_front(20);
    deq.push_front(10);
    show(deq);

    deq.push_back(40);
    deq.push_back(50);
    show(deq);

    // while(!deq.empty()) deq.pop_front();
    while(!deq.empty()) deq.pop_back();
    // deq.clear();
    show(deq);
}

int main()
{
    SLLHead<int> sll1;
    SLLHeadTail<int> sll2;
    CircularSLLTail<int> sll3;

    // testDeque(sll1);
    // testDeque(sll2);
    testDeque(sll3);

    return 0;
}
