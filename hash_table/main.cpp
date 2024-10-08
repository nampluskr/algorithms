#include "hash_table.h"
#include "linked_list.h"
#include "string.h"
#include <cstdio>


int main()
{
    if (0) {
        LinkedList<int> lst;

        lst.clear();
        lst.push_back(10);
        lst.push_back(20);
        lst.push_back(30);

        printf(">> head->");
        for (auto data: lst) printf("[%d]->", data);
        printf("null\n");

        lst.clear();
        printf(">> head->");
        for (auto data: lst) printf("[%d]->", data);
        printf("null\n");
    }
    if (0) {
        // HashTable<int, int> intMap(11);

        // printf("*** Push:\n");
        // intMap.clear();
        // intMap.emplace(10, 1);
        // intMap.emplace(20, 2);
        // intMap.emplace(30, 3);

        // printf("%d\n", intMap.find(10));
        // printf("%d\n", intMap.find(20));
        // printf("%d\n", intMap.find(30));
        // printf("%d\n", intMap.find(40));

        // // printf("(%d, %d)\n", 10, intMap[10]);
        // // printf("(%d, %d)\n", 20, intMap[20]);
        // // printf("(%d, %d)\n", 30, intMap[30]);
        // // printf("(%d, %d)\n", 40, intMap[40]);

        // printf("*** Remove:\n");
        // intMap.remove(10);
        // intMap.remove(20);
        // intMap.remove(30);
        // intMap.remove(40);
        // // intMap.clear();

        // printf("%d\n", intMap.find(10));
        // printf("%d\n", intMap.find(20));
        // printf("%d\n", intMap.find(30));
        // printf("%d\n", intMap.find(40));
    }
    if (0) {
        HashTable<String, int> strMap(11);

        strMap.clear();
        strMap.emplace("aaa", 1);
        strMap.emplace("bbb", 2);
        strMap.emplace("ccc", 3);

        printf("%d\n", strMap.find("aaa"));
        printf("%d\n", strMap.find("bbb"));
        printf("%d\n", strMap.find("ccc"));
        printf("%d\n", strMap.find("ddd"));

        printf("(%s, %d)\n", "aaa", strMap["aaa"]);
        printf("(%s, %d)\n", "bbb", strMap["bbb"]);
        printf("(%s, %d)\n", "ccc", strMap["ccc"]);
        printf("(%s, %d)\n", "ddd", strMap["ddd"]);

        printf("*** Remove:\n");
        strMap.remove("aaa");
        strMap.remove("bbb");
        strMap.remove("ccc");
        strMap.remove("ddd");

        printf("%d\n", strMap.find("aaa"));
        printf("%d\n", strMap.find("bbb"));
        printf("%d\n", strMap.find("ccc"));
        printf("%d\n", strMap.find("ddd"));
    }
    if (1) {
        HashTable<String, LinkedList<String>> listMap(11);

        listMap.clear();
        listMap["aaa"].push_back("a");
        listMap["aaa"].push_back("b");
        listMap["aaa"].push_back("c");

        // listMap.clear();
        printf(">> ");
        for (const auto data: listMap["aaa"]) printf("%s ", data.str);
        printf("\n");
    }

    return 0;
}