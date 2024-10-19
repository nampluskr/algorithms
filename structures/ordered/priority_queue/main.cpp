#include "binary_search_tree_pq.h"
#include "ordered_list_pq.h"
#include "binary_heap_pq.h"
#include <cstdio>

template<typename T>
void testPQ(T& q) {
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
    // ArrayQueue<int> q1;
    // LinkedQueue<int> q2;

    printf("\n*** Ordered List Priority Queue:\n");
    // testPQ(q1);

    printf("\n*** Binary Search Tree Priority Queue:\n");
    // testPQ(q2);

    printf("\n*** Binary Heap Priority Queue:\n");

    return 0;
}