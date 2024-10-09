#pragma once
#include <cstring>
#include <ostream>

struct String {
    char* str;
    int len;

    String(const char* other) {
        len = strlen(other);
        str = new char[len + 1];
        strcpy(str, other);
    }
    // 복사 생성자
    String (const String& other) {
        len = other.len;
        str = new char[len + 1];
        strcpy(str, other.str);
    }
    ~String() { delete[] str; }

    // getter
    const char* to_str() const { return str; }

    struct Iterator {
        char* ptr;

        Iterator(char* ptr) { this->ptr = ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        Iterator& operator++() { ptr++; return *this; }
        char& operator*() const { return *ptr; }
    };
    Iterator begin() { return Iterator(str); };
    const Iterator begin() const { return Iterator(str); };     // 수정 불가
    Iterator end() { return Iterator(str + len); }
    const Iterator end() const { return Iterator(str + len); }  // 수정 불가

#if 0 // 추가 생성자, 연상자, 메서드 정의
    // 이동 생성자
    String(String&& other) noexcept {
        str = other.str;
        len = other.len;
        other.str = nullptr;
        other.len = 0;
    }

    // 대입 연산자
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            len = other.len;
            str = new char[len + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    // 이동 대입 연산자
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] str;
            str = other.str;
            len = other.len;
            other.str = nullptr;
            other.len = 0;
        }
        return *this;
    }

    // 비교 연산자
    bool operator==(const String& other) const {
        return (len == other.len && strcmp(str, other.str) == 0);
    }

    // 인덱싱 연산자
    char& operator[](size_t index) {
        return str[index];
    }

    // const 인덱싱 연산자
    const char& operator[](size_t index) const {
        return str[index];
    }

    // 길이 반환
    size_t size() const { return len; }

    // 빈 문자열 여부 확인
    bool empty() const { return len == 0; }

    // 문자열 연결 (+= 연산자)
    String& operator+=(const String& other) {
        char* temp = new char[len + other.len + 1];
        strcpy(temp, str);
        strcat(temp, other.str);
        delete[] str;
        str = temp;
        len = strlen(str);
        return *this;
    }

    // 문자열 출력 (<< 연산자)
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.str;
        return os;
    }
#endif
};


struct StaticString {
    char str[21];
    int len;

    StaticString(const char* other) {
        len = strlen(other);
        strcpy(str, other);
    }
    // 복사 생성자
    StaticString (const StaticString& other) {
        len = other.len;
        strcpy(str, other.str);
    }
    // getter
    const char* to_str() const { return str; }

    struct Iterator {
        const char* ptr;

        Iterator(const char* ptr) { this->ptr = ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        Iterator& operator++() { ptr++; return *this; }
        const char& operator*() const { return *ptr; }
    };
    Iterator begin() { return Iterator(str); };
    const Iterator begin() const { return Iterator(str); };
    Iterator end() { return Iterator(str + len); }
    const Iterator end() const { return Iterator(str + len); }

};