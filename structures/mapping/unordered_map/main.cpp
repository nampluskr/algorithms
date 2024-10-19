#include "hash_map.h"
#include "../map/ordered_list_map.h"
#include "../map/binary_search_map.h"
#include <cstdio>

template<typename T>
void testIntMap(T& map) {
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

template<typename T>
void testStrMap(T& map) {
    map.clear();
    map.emplace("aaa", 1);
    map.emplace("bbb", 2);
    map.emplace("ccc", 3);

    printf(">> (%s, %d)\n", "aaa", map["aaa"]);
    printf(">> (%s, %d)\n", "bbb", map["bbb"]);
    printf(">> (%s, %d)\n", "ccc", map["ccc"]);
    printf(">> (%s, %d)\n", "ddd", map["ddd"]);

    printf("\n");
    map.erase("aaa");
    map.emplace("ddd", 4);

    printf(">> (%s, %d)\n", "aaa", map["aaa"]);
    printf(">> (%s, %d)\n", "bbb", map["bbb"]);
    printf(">> (%s, %d)\n", "ccc", map["ccc"]);
    printf(">> (%s, %d)\n", "ddd", map["ddd"]);
}

int main()
{
    if (1) {
        HashMap<int, int, OrderedListMap<int, int>> m1;
        HashMap<int, int, BinarySearchMap<int, int>> m2;
        HashChaining<int, int> m3;

        printf("\n*** Hash Chaining Using Ordered List Map:\n");
        testIntMap(m1);
        printf("\n*** Hash Chaining Using Binary Search Map:\n");
        testIntMap(m2);
        printf("\n*** Hash Chaining:\n");
        testIntMap(m3);
    }

    if (0) {
        HashMap<const char*, int, OrderedListMap<const char*, int>> h1;
        HashMap<const char*, int, BinarySearchMap<const char*, int>> h2;
        HashChaining<const char*, int> h3;

        printf("\n*** Hash Chaining Using Ordered List Map:\n");
        testStrMap(h1);
        printf("\n*** Hash Chaining Using Binary Search Map:\n");
        testStrMap(h2);
        printf("\n*** Hash Chaining:\n");
        testStrMap(h3);
    }

    return 0;
}