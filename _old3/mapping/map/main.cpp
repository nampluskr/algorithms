#include "bstmap.h"
#include "listmap.h"
#include <cstdio>
#include <map>

template<typename T>
void testHashTable(T& map) {
    map.emplace(100, 1);
    map.emplace(200, 2);
    map.emplace(300, 3);

    printf(">> key=%d, value=%d\n", 100, map[100]);
    printf(">> key=%d, value=%d\n", 200, map[200]);
    printf(">> key=%d, value=%d\n", 300, map[300]);
    printf(">> key=%d, value=%d\n", 400, map[400]);
    printf("\n");

    map.erase(100);
    printf(">> key=%d, value=%d\n", 100, map[100]);
    printf(">> key=%d, value=%d\n", 200, map[200]);
    printf(">> key=%d, value=%d\n", 300, map[300]);
    printf(">> key=%d, value=%d\n", 400, map[400]);
    printf("\n");
}


int main()
{
    std::map<int, int> m1;
    BSTMapRecur<int, int> m2;
    ListMap<int, int> m3;

    testHashTable(m1);
    testHashTable(m2);
    testHashTable(m3);

    return 0;
}