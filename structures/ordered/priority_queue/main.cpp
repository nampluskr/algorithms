#include "sll_priority_queue.h"
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
    sll_priority_queue<int> pq2;

    testPrioirtyQueue(pq1);
    testPrioirtyQueue(pq2);

    return 0;
}
