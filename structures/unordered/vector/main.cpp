#include <vector>
#include <cstdio>
#include "sll_vector.h"
#include "array_vector.h"

template<typename T>
void testVector(T& vec) {
    vec.clear();

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    printf(">> ");
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
        printf("[%d]->", *iter);
    printf("\n");

    printf(">> ");
    for (const auto& data: vec)
        printf("[%d]->", data);
    printf("\n");
}


int main()
{
    std::vector<int> v1;
    sll_vector<int> v2;
    array_vector_static<int> v3(10);
    array_vector_dynamic<int> v4(10);

    testVector(v1);
    testVector(v2);
    testVector(v3);
    testVector(v4);

    return 0;
}