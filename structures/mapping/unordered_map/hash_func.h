#pragma once
#include <cstring>

using ull = unsigned long long;

// 사용자 정의 해시 함수
template<typename K>
ull hash_func(const K& key, int maxTable);

// 정수에 대한 해시 함수
template<>
ull hash_func<int>(const int& key, int maxTable) {
    return key % maxTable;
}

// C 스타일 문자열에 대한 해시 함수
template<>
ull hash_func<const char*>(const char* const & key, int maxTable) {
    ull hash = 0;
    for (int i = 0; i < strlen(key); i++)
        hash = hash * 31 + key[i];
    return hash % maxTable;
}