#include <cstdio>
#include "array_list.h"
#include "linked_list.h"
#include "linked_map.h"
#include "binary_search_tree.h"
#include "binary_search_map.h"
#include "binary_heap.h"
#include "ordered_linked_list.h"
#include "ordered_linked_map.h"
#include "hashmap.h"

template<typename T>
void testList(T& lst) {
    printf("\n");
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    lst.push_back(50);
    lst.push_back(60);
    lst.push_back(70);
    lst.push_back(80);
    lst.push_back(90);

    printf(">> ");
    for (auto data : lst) printf("[%d]->", data);
    printf("\n");

    printf(">> ");
    while (!lst.empty()) {
        auto data = lst.back(); lst.pop_back();
        printf("[%d]->", data);
    }
    printf("\n");
}

template<typename T>
void testSet(T& set) {
    printf("\n");
    set.insert(30);
    set.insert(50);
    set.insert(20);
    set.insert(10);
    set.insert(40);
    //set.show();

    //set.remove(20); set.show();
    //set.remove(10); set.show();
    //set.remove(50); set.show();
    //set.remove(30); set.show();
    //set.remove(40); set.show();

    while (!set.empty()) {
        auto data = set.top(); set.pop();
        printf("Top=%d: ", data); // set.show();
    }
}

template<typename T>
void testHashMap(T& map) {
    printf("\n");
    map.emplace(100, 1);
    map.emplace(200, 2);
    map.emplace(300, 3);

    printf(">> (%d, %d)\n", 100, map[100]);
    printf(">> (%d, %d)\n", 200, map[200]);
    printf(">> (%d, %d)\n", 300, map[300]);
    printf(">> (%d, %d)\n", 400, map[400]);

    printf("\n");
    map.remove(100);
    map.emplace(400, 4);

    printf(">> (%d, %d)\n", 100, map[100]);
    printf(">> (%d, %d)\n", 200, map[200]);
    printf(">> (%d, %d)\n", 300, map[300]);
    printf(">> (%d, %d)\n", 400, map[400]);
}


int main()
{
    //ArrayList<int> l1;
    //LinkedList<int> l2;

    //testList(l1);
    //testList(l2);

    OrderedLinkedList<int> s1;
    BinarySearchTree<int> s2;
    BinaryHeap<int> s3;

    testSet(s1);
    testSet(s2);
    testSet(s3);

    //OrderedLinkedMap<int, int> h1;
    //BinarySearchMap<int, int> h2;
    //HashChaining<int, int> h3;
    //HashMap<int, int, OrderedLinkedMap<int, int>> h4;
    //HashMap<int, int, BinarySearchMap<int, int>> h5;
    //HashMap<int, int, LinkedMap<int, int>> h6;

    //testHashMap(h6);

    return 0;
}
