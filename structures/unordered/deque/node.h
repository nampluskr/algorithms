#pragma once

template<typename T>
struct SingleNode {
    T data;
    SingleNode* next;
};

template<typename T>
struct DoubleNode {
    T data;
    DoubleNode* prev;
    DoubleNode* next;
};

