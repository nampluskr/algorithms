# Hash Functions

## 사용자 정의 해시 함수

```cpp
// 사용자 정의 해시 함수
template<typename K>
ull hash_func(const K& key, int maxTable);

// 정수에 대한 해시 함수
template<>
ull hash_func<int>(const int& key, int maxTable) {
    return key % maxTable; // division_hash
}

// C 스타일 문자열에 대한 해시 함수
template<>
ull hash_func<const char*>(const char* const & key, int maxTable) {
    ull hash = 0;
    for (int i = 0; i < strlen(key); i++)
        hash = hash * 31 + c;    // horner_hash
    return hash % maxTable;
}
```

## 정수형 해시 함수

### Divistion 해시 함수

```cpp
int division_hash(const int& key, int maxTable) {
    return key % maxTable;
}
```

### Multiplication 해시 함수

```cpp
ull hash_val = table_size * ((key * A) - static_cast<ull>(key * A));
ull hash_val = static_cast<ull>(table_size * (key * A - static_cast<ull>(key * A)));

ull multiplication_hash(const int& key, int maxTable) {
    double A = (sqrt(5) - 1) / 2;
    double t = key * A;
    return (int)(t * maxTable) % maxTable;
}

ull multiplication_hash(const int& key, int maxTable) {
    ull hash = key * 2654435769;        // Knuth의 상수 값 사용 = 2^32 * (sqrt(5) - 1) / 2
    return (hash >> 32) % maxTable;     // 상위 32비트를 취해서 해시 값을 얻음
}
```

### Knuth 해시 함수

```cpp
#define KNUTH_MAX_TABLE     (1 << 20)  // 1024 * 1024: 2의 거듭 제곱 형태, 2^n

int knuth_hash(const int& key) {
    ull hash = key * 2654435769;  // 2^32 * (sqrt(5) - 1) / 2
    return hash & (KNUTH_MAX_TABLE - 1);
}
```

### Universal 해시 함수
- 작은 해시 테이블 `M = 1000`: `a = 31`, `b = 17`, `P = 1000003`
- 큰 해시 테이블 `M = 1000000`: `a = 1664525`, `b = 1013904223`, `P = 2147483647` (`int`형 최대값)

```cpp
ull universal_hash(const int& key, int maxTable) {
    ull a = 31, b = 17, prime = 1000003;                    // 작은 해시 테이블 (1'000)
    ull a = 1664525, b = 1013904223, prime = 2147483647;    // 큰 해시 테이블 (1'000'000)
    return ((a * key + b) % prime) % maxTable;
}
```

### Perfect 해시 함수
- 모든 주어진 입력값을 고유하게 매핑하는 해시 함수로 이상적으로는 충돌이 전혀 발생하지 않도록 설계됨
- 해시 테이블의 모든 요소에 대해 단 하나의 해시 값을 생성함
- 데이터베이스, 컴파일러와 같은 애플리케이션에서 매우 유용

```cpp
int perfect_hash(const int& key, vector<int>& hashTable) {
    int M = hashTable.size();
    int index = key % M;        // 단순한 해시 함수

    // 충돌이 발생하면 다음 빈 위치를 찾음 (선형 탐사)
    while (hashTable[index] != -1)
        index = (index + 1) % M;

    // 해시 테이블에 값 저장
    hashTable[index] = key;
    return index;
}

int main() {
    int M = 101; // 해시 테이블 크기 (모든 입력값이 0부터 100까지라고 가정)
    vector<int> hashTable(M, -1); // 해시 테이블 초기화 (-1은 빈 위치를 나타냄)

    // 예제 입력값
    vector<int> inputs = {5, 18, 25, 33, 44, 59, 78, 99, 100};
    for (int x : inputs) {
        int hashIndex = perfectHash(x, hashTable);
        cout << "The value " << x << " is stored at index " << hashIndex << endl;
    }

    return 0;
}
```


## 문자열 해시 함수

### Horner 해시 함수
- Horner's Method를 사용해 해시 값을 계산

```cpp
ull horner_hash(const char* const & key, int maxTable) {
    ull hash = 0;
    int c;
    while (c = *key++) hash = hash * 31 + c;
    return hash % maxTable;
}
```

### FNV-1a(Fowler-Noll-Vo) 해시 함수
- 각 문자에 대해 XOR 연산을 수행한 후, 특정 소수(prime)와의 곱셈을 통해 해시 값을 생성

```cpp
ull fnv_1a_hash(const char* const & key, int maxTable) {
    ull hash = 2166136261;      // FNV_OFFSET_BASIS = 14695981039346656037ULL
    ull prime = 16777619;       // FNV_PRIME = 1099511628211ULL
    int c;
    while (c = *key++) hash = (hash ^ c) * prime;
    return hash % maxTable;
}
```

### Dan Bernstein 해시 함수
- 문자열의 각 문자를 순회하며 해시 값을 계산하고, 각 문자의 ASCII 값과 곱셈을 통해 해시 값을 업데이트
- 주로 문자열 해싱에 사용되며, 빠르고 고르게 분포하는 특징

```cpp
ull djb2_hash(const char* const & key, int maxTable) {
    ull hash = 5381;
    int c;
    while (c = *key++)
        hash = (((hash << 5) + hash) + c) % maxTable; // hash * 33 + c
    return hash % maxTable;
}
```

### Rolling 해시 함수
- 주로 문자열 검색 알고리즘에서 사용
- 슬라이딩 윈도우 방식으로 이전 해시 값을 이용해 새로운 해시 값을 빠르게 계산
- 긴 문자열에서 일정 구간의 해시 값을 효율적으로 계산: 라빈-카프(Rabin-Karp) 알고리즘

```cpp
ull rolling_hash(const char* const & key, int maxTable) {
    ull MOD = 1e9 + 7, BASE = 31;
    ull hash = 0, pow = 1;
    int c;
    while (c = *key++) {
        hash = (hash + (c - 'a' + 1) * pow) % MOD;
        pow = (pow * BASE) % MOD;
    }
    return hash % maxTable;
}
```