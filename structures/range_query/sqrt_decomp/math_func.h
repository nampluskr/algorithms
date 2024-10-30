#pragma once

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }
inline int ceil(int a, int b) { return (a + b - 1) / b; }

int sqrt(int n) {
    bool decreased = false;
    int x = n, nx = (x + n / x) >> 1;
    while (true) {
        if (x == nx || (x < nx && decreased)) break;
        decreased = x > nx;
        x = nx, nx = (x + n / x) >> 1;
    }
    return x;
}