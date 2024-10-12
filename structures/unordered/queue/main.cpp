#include <queue>
#include "sll_queue.h"
#include "array_queue.h"
#include <cstdio>

template<typename T>
void testQueue(T& que) {
    // que.clear();
    while(!que.empty()) que.pop();

    que.push(10);
    que.push(20);
    que.push(30);

    while(!que.empty()) {
        auto data = que.front(); que.pop();
        printf(">> Top = [%d]\n", data);
    }
}


int main()
{
    std::queue<int> q1;
    sll_queue<int> q2;
    array_queue<int> q3(10);

    // testQueue(q1);
    // testQueue(q2);
    testQueue(q3);

    return 0;
}