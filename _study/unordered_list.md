### linked_list.h

```cpp
#pragma once

template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    int listSize;

    LinkedList() { head = nullptr; listSize = 0; }
    ~LinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head ->next;
            delete temp;
        }
        listSize = 0;
    }
    bool empty() { return head == nullptr; }
    int size() { return listSize; }
    T back() { return head->data; }

    void push_back(const T& data) {
        head = new Node{ data, head };
        listSize++;
    }
    void pop_back() {
        Node* temp = head;
        head = head->next;
        delete temp;
        listSize--;
    }
    T* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return &curr->data;
            curr = curr->next;
        }
        return nullptr;
    }
    void erase(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) break;
            curr = curr->next;
        }
        if (curr == nullptr) return;    // No data
        if (prev == nullptr) head = nullptr;
        else prev->next = curr->next;
        delete curr;
        listSize--;
    }

    struct Iterator{
        Node* ptr;

        Iterator(Node* ptr) { this->ptr = ptr; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return !(ptr == other.ptr); }
        Iterator operator++() { ptr = ptr->next; return *this; }
        T& operator*() { return ptr->data; }
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};
```

### array_list.h

```cpp
#pragma once

template<typename T>
struct ArrayList {
    T* arr;
    int arrSize;
    int capacity;

    ArrayList(int capacity = 2) {
        arr = new T[capacity];
        this->capacity = capacity;
        arrSize = 0;
    }
    ~ArrayList() { delete[] arr; }

    void clear() { arrSize = 0; }
    bool empty() { return arrSize == 0; }
    int size() { return arrSize; }
    T back() { return arr[arrSize - 1]; }

    void push_back(const T& data) { 
        if (arrSize == capacity) resize(capacity * 2);
        arr[arrSize++] = data;
    }
    void pop_back() { arrSize--; }
    T* find(const T& data) {
        for (int i = 0; i < arrSize; i++)
            if (arr[i] == data) return arr + i;
        return nullptr;
    }
    void erase(const T& data) {
        T* res = find(data);
        if (res != nullptr) {
            if (res != &arr[arrSize - 1]) res = &arr[arrSize - 1];
            arrSize--;
        }
    }
    T* begin() { return arr; }
    T* end() { return arr + arrSize; }

private:
    void resize(int capacity) {
        T* newArr = new T[capacity];
        for (int i = 0; i < arrSize; i++) newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        this->capacity = capacity;
    }
};
```

### main.cpp

```cpp
#include <cstdio>
#include "linked_list.h"
#include "array_list.h"
#include <vector>

template<typename T>
void testList(T& lst) {
    printf("\n");
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    lst.push_back(50);
    lst.push_back(60);
    lst.push_back(70);
    lst.push_back(80);
    lst.push_back(90);

    printf(">> ");
    for (auto data : lst) printf("[%d]->", data);
    printf("\n");

    printf(">> ");
    while (!lst.empty()) {
        auto data = lst.back(); lst.pop_back();
        printf("[%d]->", data);
    }
    printf("\n");
}


int main()
{
    std::vector<int> l0;
    LinkedList<int> l1;
    ArrayList<int> l2;

    testList(l0);
    testList(l1);
    testList(l2);

    return 0;
}
```
