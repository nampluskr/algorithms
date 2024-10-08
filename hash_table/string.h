#pragma once
#include <cstring>  // strlen(), strcpy(), strcmp()


// struct String {
//     char* str;
//     int len;

//     // 생성자
//     String(const char* s) {
//         len = strlen(s);
//         str = new char[len + 1];
//         strcpy(str, s);
//     }
//     // // 복사 생성자 (double free error 방지)
//     String(const String& other) {
//         len = other.len;
//         str = new char[len + 1];
//         strcpy(str, other.str);
//     }
//     // 소멸자
//     ~String() { delete[] str; }

//     bool operator==(const String& other) const {
//         return len == other.len && strcmp(str, other.str) == 0;
//     }
//     // 인덱싱 연산자
//     char& operator[](int index) {
//         return str[index];
//     }
//     // const 인덱싱 연산자
//     const char& operator[](int index) const {
//         return str[index];
//     }

//     // for (Iterator iter = begin(); iter != end(); ++iter) { *this; }
//     struct Iterator {
//         char* ptr;

//         Iterator(char* p) : ptr(p) {}
//         bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
//         Iterator& operator++() { ++ptr; return *this; }
//         char& operator*() const { return *ptr; }
//     };
//     Iterator begin() const { return Iterator(str); }        // const
//     Iterator end() const { return Iterator(str + len); }
// };


struct String {
    char str[21];   // const char*
    int len;

    // 생성자
    String(const char* s) {
        len = strlen(s);
        strcpy(str, s);
    }
    // // 복사 생성자 (double free error 방지)
    // String(const String& other) {
    //     len = other.len;
    //     strcpy(str, other.str);
    // }

    bool operator==(const String& other) const {
        return len == other.len && strcmp(str, other.str) == 0;
    }
    // 인덱싱 연산자
    char& operator[](size_t index) {
        return str[index];
    }
    // const 인덱싱 연산자
    const char& operator[](int index) const {
        return str[index];
    }

    // for (Iterator iter = begin(); iter != end(); ++iter) { *this; }
    struct Iterator {
        const char* ptr;

        Iterator(const char* p) : ptr(p) {}
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        const char& operator*() const { return *ptr; }
    };
    const Iterator begin() const { return Iterator(str); }
    const Iterator end() const { return Iterator(str + len); }
};