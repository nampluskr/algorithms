#include <cstdio>
#include <cstring>

struct String {
    char* str;
    int len;

    String(const char* s) {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
    }
    ~String() { delete[] str; }

    struct Iterator {
        char* ptr;

        Iterator(char* p) : ptr(p) {}
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        const char& operator*() const { return *ptr; }
    };
    Iterator begin() const { return Iterator(str); }
    Iterator end() const { return Iterator(str + len); }
};

int main() {
    const String str = "abced";

    printf(">> ");
    for (char c: str) printf("%c", c); // 이제 에러가 발생하지 않습니다.
    printf("\n");

    return 0;
}