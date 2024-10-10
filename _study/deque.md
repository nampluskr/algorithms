## SLL

### Singly Linked List with Head Node

```cpp
template<typename T>
struct SLLHead {
    Node<T>* head = nullptr;

    void push_front(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    void push_back(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = newNode;
        else {
            Node<T>* curr = head;
            while (curr->next != nullptr) curr = curr->next;
            curr->next = newNode;
        }
    }
    void pop_back() {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;   // head != nullptr
        while (curr->next != nullptr) { prev = curr; curr = curr->next; }

        if (prev == nullptr) head = nullptr;
        else prev->next = nullptr;
        delete curr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> head->");
        Node<T>* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
        printf("null\n");
    }
};
```

### Singly Linked List with Head and Tail Nodes

```cpp
template<typename T>
struct SLLHeadTail {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    void push_front(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head = newNode; }
    }
    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    void push_back(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    void pop_back() {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;   // head != nullptr
        while (curr != tail) { prev = curr; curr = curr->next; }

        if (prev == nullptr) head = tail = nullptr;
        else { prev->next = nullptr; tail = prev; }
        delete curr;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> head->");
        Node<T>* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
        printf("null\n");
    }
};
```

### Circular Singly Linked List with Tail Node

```cpp
template<typename T>
struct CircularSLLTail {
    Node<T>* tail = nullptr;

    void push_front(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr };
        if (tail == nullptr) { tail = newNode; tail->next = tail; }
        else { newNode->next = tail->next; tail->next = newNode; }
    }
    void pop_front() {
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node<T>* temp = tail->next;
            tail->next = temp->next;
            delete temp;
        }
    }
    void push_back(const T& data) {
        push_front(data);
        tail = tail->next;
    }
    void pop_back() {
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node<T>* temp = tail;
            while (tail->next != temp) tail = tail->next;
            pop_front();
        }
    }
    bool empty() { return tail == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> ");
        if (tail != nullptr) {
            if (tail->next == tail) printf("[%d]->", tail->data);
            else {
                Node<T>* curr = tail->next;
                while (curr != tail) {
                    printf("[%d]->", curr->data);
                    curr = curr->next;
                }
                printf("[%d]->", curr->data);
            }
        }
        printf("\n");
    }
};
```

## Doublly Linked List

### Dboublly Linked List with Head and Tail Nodes

```cpp
template<typename T>
struct DLLHeadTail {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    void push_front(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->next = head; head->prev = newNode; head = newNode; }
    }
    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        else head->prev = nullptr;
        delete temp;
    }
    void push_back(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
        if (head == nullptr) head = tail = newNode;
        else { newNode->prev = tail; tail->next = newNode; tail = newNode; }
    }
    void pop_back() {
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail == nullptr) head = nullptr;
        else tail->next = nullptr;
        delete temp;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> head->");
        Node<T>* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }
        printf("null\n");
    }
};
```

### Circular Doubly Linked List with Head Node

```cpp
template<typename T>
struct CircularDLLHead {
    Node<T>* head = nullptr;

    void push_front(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
        if (head == nullptr) {
            newNode->prev = newNode->next = newNode;
            head = newNode;
        }
        else {
            Node<T>* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = head->prev = newNode;
            head = newNode;
        }
    }
    void pop_front() {
        Node<T>* temp = head;
        if (head == head->prev) head = nullptr;
        else {
            Node<T>* tail = head->prev;
            head = head->next;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
    }
    void push_back(const T& data) {
        Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
        if (head == nullptr) {
            newNode->prev = newNode->next = newNode;
            head = newNode;
        }
        else {
            Node<T>* tail = head->prev;
            newNode->next = head;
            head->prev = newNode;
            newNode->prev = tail;
            tail->next = newNode;
        }
    }
    void pop_back() {
        Node<T>* temp = head->prev;
        if (head == head->prev) head = nullptr;
        else {
            Node<T>* tail = head->prev->prev;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
    }
    bool empty() { return head == nullptr; }
    void clear() { while (!empty()) pop_front(); }
    void show() {
        printf(">> head->");
        if (head != nullptr) {
            if (head->next == head) printf("[%d]->", head->data);
            else {
                Node<T>* curr = head;
                while (curr->next != head) {
                    printf("[%d]->", curr->data);
                    curr = curr->next;
                }
                printf("[%d]->", curr->data);
            }
        }
        printf("null\n");
    }
};
```

## Array Deque

```cpp
template<typename T>
struct ArrayDeque {
    T* arr;
    int head, tail;
    int max_size;

    ArrayDeque(int max_size) { 
        this->max_size = max_size;
        arr = new T[max_size];
        head = tail = 0;
    }
    ~ArrayDeque() { delete[] arr; }

    void push_front(const T& data) {
        if ((tail + 1) % max_size == head) return;   // overflow
        head = (head - 1 + max_size) % max_size;
        arr[head] = data;
    }

    void pop_front() {
        if (head == tail) return;
        head = (head + 1) % max_size;
    }

    void push_back(const T& data) {
        if ((tail + 1) % max_size == head) return;   // overflow
        arr[tail] = data;
        tail = (tail + 1) % max_size;
    }

    void pop_back() {
        if (head == tail) return;
        tail = (tail - 1 + max_size) % max_size;
    }
    bool empty() { return head == tail; }
    void clear() { head = tail = 0; }
    void show() const {
        printf(">> head->");
        if (head != tail) {
            int curr = head;
            do {
                printf("[%d]->", arr[curr]);
                curr = (curr + 1) % max_size;
            } while (curr != tail);
        }
        printf("null\n");
    }
};
```
