#pragma once
#include "string.h"

// base: 작은 소수
// P: 큰 소수 (1e + 7,  2147483647 = 2^31 - 1 = (1 << 31) - 1)
// M = 1000; // 해시 테이블 크기

template<typename Key>
int hashFunc(const Key& key, int maxTable) { return 0; }

// Horner's method
int horner(const String& str, int maxTable) {
    unsigned long long hash = 0;
    for (char c : str)
        hash = hash * 31 + c;
    return hash % maxTable;
}

int fnv_1a(const String& str, int maxTable) {
    unsigned long long hash = 2166136261;
    const unsigned int p = 16777619;
    for (char c : str)
        hash = (hash ^ c) * p;
    return hash % maxTable;
}

//  Dan Bernstein
int djb2(const String& key, int maxTable) {
    unsigned long long hash = 5381;
    for (char c: key)
        hash = ((hash << 5) + hash) + c;
    return hash % maxTable;
}

// Rolling Hash Function
int rollingHash(const String& str, int maxTable) {
    unsigned long long hash = 0;
    unsigned long p_pow = 1;
    int p = 31;         // 소수
    int M = 1e9 + 7;    // 큰 소수

    for (char c : str) {
        hash = (hash + (c - 'a' + 1) * p_pow) % M;
        p_pow = (p_pow * p) % M;
    }
    return hash % maxTable;
}

// base = 31, M = 1e9 + 7
unsigned long long polynomialRollingHash(const String& str, int base, int M) {
    int n = str.len;
    unsigned long long hash = 0, base_pow = 1;
    for (int i = 0; i < n; i++) {
        hash = (hash * base + str[i]) % M;
        base_pow = (base_pow * base) % M;
    }
    return hash;
}

int rabinKarpHash(const String& str, int base, int M) {
    unsigned long long hash = 0;
    for (int i = 0; i < str.len; i++)
        hash = (hash * base + str[i]) % M;
    return hash;
}

template<>
int hashFunc(const String& key, int maxTable) {
    horner(key, maxTable);
}

template<>
int hashFunc(const int& key, int maxTable) {
    return key % maxTable;
}

int divisionHash(int x, int M) {
    return x % M;
}

// Knuth
// int multiplicationHash(int x, int M, int A) {
//     // A는 0과 1 사이의 상수 (일반적으로 황금비율 (sqrt(5) - 1) / 2를 사용)
//     double A = (sqrt(5) - 1) / 2;
//     double t = x * A;
//     return (int)(t * M) % M;
// }

// a, b: 임의의 소수
// P: 충분히 큰 소수 (M보다 커야 함)
// a, b, M(해시테이블 크기), P(큰 소수)
// 31, 17, 1000, 1000003: 작은 해시 테이블에 적합한 예시
// 1664525, 1013904223, 1000000, 2147483647(int형 최댓값): 큰 해시 테이블에 적합한 예시 
// 13, 7, 256, 4099 : 작은 해시 테이블에 적합한 예시, P는 M보다 약간 큰 소수
// a = 31, b = 17 / a = 9973, b = 19997 / a = 12345, b = 67890
// a = 16777619, b = 3344443 / a = 99999973, b = 199999997 / a = 123456789, b = 987654321
// int universalHash(int x, int M, int a, int b) {
//     return ((a * x + b) % P) % M; // P는 충분히 큰 소수
// }

// 모든 입력값이 0부터 100까지라고 가정
int perfectHash(int x) {
    int hashTable[101]; // 충분히 큰 배열 할당
    // 모든 입력값을 순회하며 해시 테이블에 저장 (충돌 발생 시 다른 위치에 저장)
    // ... (충돌 처리 로직 생략)
    return hashTable[x];
}
