#include "sll_priority_queue.h"
#include "bst_priority_queue.h"
#include <cstdio>
#include <queue>

template<typename T>
void testPrioirtyQueue(T& pq) {
    pq.push(30);
    pq.push(50);
    pq.push(20);
    pq.push(10);
    pq.push(40);

    printf(">> Top = ");
    while (!pq.empty()) {
        auto data = pq.top(); pq.pop();
        printf("%d > ", data);
    }
    printf("\n");
}

int main()
{
    std::priority_queue<int> pq1;
    sll_priority_queue_recur<int> pq2;
    sll_priority_queue_iter<int> pq3;
    bst_priority_queue_recur<int> pq4;
    bst_priority_queue_iter<int> pq5;

    testPrioirtyQueue(pq1);
    testPrioirtyQueue(pq2);
    testPrioirtyQueue(pq3);
    testPrioirtyQueue(pq4);
    testPrioirtyQueue(pq5);

    return 0;
}
