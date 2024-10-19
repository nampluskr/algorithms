#include "ordered_list_map.h"
#include "binary_search_map.h"
#include <cstdio>

template<typename T>
void testMap(T& map) {
    map.clear();
    map.emplace(100, 1);
    map.emplace(200, 2);
    map.emplace(300, 3);

    printf(">> (%d, %d)\n", 100, map[100]);
    printf(">> (%d, %d)\n", 200, map[200]);
    printf(">> (%d, %d)\n", 300, map[300]);
    printf(">> (%d, %d)\n", 400, map[400]);

    printf("\n");
    map.erase(100);
    map.emplace(400, 4);
    // map[400] = 4;

    printf(">> (%d, %d)\n", 100, map[100]);
    printf(">> (%d, %d)\n", 200, map[200]);
    printf(">> (%d, %d)\n", 300, map[300]);
    printf(">> (%d, %d)\n", 400, map[400]);
}

int main()
{
    OrderedListMap<int, int> m1;
    BinarySearchMap<int, int> m2;

    printf("\n*** Ordered List Map:\n");
    testMap(m1);

    printf("\n*** Binary Search Map:\n");
    testMap(m2);

    return 0;
}