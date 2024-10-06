#include "list.h"
#include <cstdio>
#include <vector>

template<typename T>
void testList(T& li) {
    li.clear();
    li.push_back(20);
    li.push_back(10);
    li.push_back(30);
    li.push_back(40);
    li.push_back(50);

    printf(">> size=%d\n", (int)li.size());
    for (int data: li) printf("[%d] ", data);
    printf("\n");
    for (auto iter = li.begin(); iter != li.end(); ++iter)
        printf("[%d] ", *iter);
    printf("\n");

    li.clear();
    printf(">> size=%d\n", (int)li.size());
    for (int data: li) printf("[%d] ", data);
    printf("\n");
}

int main()
{
    std::vector<int> vec;
    LinkedList linkedList;
    ArrayList arrayList(100);

    testList(vec);
    testList(linkedList);
    testList(arrayList);

    return 0;
}