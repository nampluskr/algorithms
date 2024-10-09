#include "string.h"
#include <cstdio>
#include <vector>
#include <string>

template<typename T>
void testString() {
    T s = "abced";
    // const T& s = "abced";
    // const T& s = "abced";
    std::vector<T> vecList;

    // Iterator
    for (auto iter = s.begin(); iter != s.end(); ++iter) printf("%c", *iter);
    printf("\n");

    // ranged-for
    for (auto c: s) printf("%c", c);
    printf("\n");

    // double free error: 복사 생성자 필요
    vecList.push_back("abc");
    vecList.push_back("dfg");
    vecList.push_back("hij");

    for (const auto& s: vecList)
        // printf("%s\n", s.str);
        printf("%s\n", s.to_str());
}

int main()
{
    testString<String>();
    testString<StaticString>();

    String s = "abced";
    printf("%s\n", s.to_str());

    return 0;
}