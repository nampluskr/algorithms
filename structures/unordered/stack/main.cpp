#include <stack>
#include "sll_stack.h"
#include "array_stack.h"
#include <cstdio>

template<typename T>
void testStack(T& stk) {
    // stk.clear();
    while(!stk.empty()) stk.pop();

    stk.push(10);
    stk.push(20);
    stk.push(30);

    while(!stk.empty()) {
        auto data = stk.top(); stk.pop();
        printf(">> Top = [%d]\n", data);
    }
}


int main()
{
    std::stack<int> s1;
    sll_stack<int> s2;
    array_stack<int> s3(10);

    // testStack(s1);
    // testStack(s2);
    testStack(s3);

    return 0;
}