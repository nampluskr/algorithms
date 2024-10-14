### BST

```cpp
#pragma once
#include <stack>
#include <cstdio>

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
};

template<typename T>
struct bst_set_recur {
    using Node = TreeNode<T>;
    Node* root;

    bst_set_recur() { root = nullptr; }
    ~bst_set_recur() { clear(); }

    void clear() { clearRecur(root); }
    Node* find(const T& data) { return findRecur(root, data); }
    void insert(const T& data) { root = insertRecur(root, data); }
    void remove(const T& data) { root = removeRecur(root, data); }

    void clearRecur(Node* node) {
        // postorder deletion
        if (node == nullptr) return;
        clearRecur(node->left);
        clearRecur(node->right);
        delete node;
    }
    Node* findRecur(Node* node, const T& data) const {
        if (node == nullptr) return nullptr;
        if (data == node->data) return node;
        else if (data < node->data) return find(node->left, data);
        else return find(node->right, data);
    }
    Node* insertRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr, nullptr };
        if (data == node->data) return node;    // No duplicates
        else if (data < node->data) node->left = insertRecur(node->left, data);
        else node->right = insertRecur(node->right, data);
        return node;
    }
    Node* removeRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
                return node;

                //Node* left = node->left;
                //delete node;
                //return left;
            }
            else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
                return node;

                //Node* right = node->right;
                //delete node;
                //return right;
            }
            else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = removeRecur(node->right, node->data);
            }
        }
        if (data < node->data) node->left = removeRecur(node->left, data);
        else node->right = removeRecur(node->right, data);
        return node;
    }
    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        else return findMin(node->left);
    }
    void show() { printf(">> "); inOrder(root); printf("\n"); }
    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        printf("[%d]->", node->data);
        inOrder(node->right);
    }
};

template<typename T>
struct bst_set_iter {
    using Node = TreeNode<T>;
    Node* root;

    bst_set_iter() { root = nullptr; }
    ~bst_set_iter() { clear(); }

    void clear() {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // 왼쪽 자식이 없으면 오르쪽으로 이동
                Node* temp = curr;
                curr = curr->right;
            } else {
                // 왼쪽 자식이 있을 경우 중위 선행자를 찾아야 함
                prev = curr->left;
                while (prev->right != nullptr && prev->right != curr)
                    prev = prev->right;

                if (prev->right == nullptr) {
                    // 중위 선행자의 오른쪽을 현재 노드로 연결
                    prev->right = curr;
                    curr = curr->left;
                } else {
                    // 중위 선행자의 오른쪽이 현재 노드로 연결된 경우
                    prev->right = nullptr;
                    Node* temp = curr;
                    curr = curr->right;
                    delete temp;
                }
            }
        }
        root = nullptr;

        //if (root == nullptr) return;
        //std::stack<Node*> S;
        //S.push(root);
        //while (!S.empty()) {
        //    Node* curr = S.top(); S.pop();
        //    if (curr->right) S.push(curr->right);
        //    if (curr->left) S.push(curr->left);
        //    delete curr;
        //}
        //root = nullptr;
    }
    Node* find(const T& data) {
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            else if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return;    // No duplicates
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        Node* newNode = new Node{ data, nullptr, nullptr };
        if (prev == nullptr) root = newNode;
        else if (data < prev->data) prev->left = newNode;
        else prev->right = newNode;
    }
    void remove(const T& data) {
        Node* prev = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        if (curr == nullptr) return;   // No data

        if (curr->left == nullptr) {
            if (prev == nullptr) root = curr->right;
            else if (prev->left == curr) prev->left = curr->right;
            else prev->right = curr->right;
            //delete curr;
            //return;
        }
        else if (curr->right == nullptr) {
            if (prev == nullptr) root = curr->left;
            else if (prev->left == curr) prev->left = curr->left;
            else prev->right = curr->left;
            //delete curr;
            //return;
        }
        else {
            Node* _prev = curr;
            Node* _curr = curr->right;
            while (_curr->left != nullptr) {
                _prev = _curr;
                _curr = _curr->left;
            }
            curr->data = _curr->data;
            if (_prev->left == _curr) _prev->left = _curr->right;
            else _prev->right = _curr->right;
            curr = _curr;
        }
        delete curr;
        //return;
    }
    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }
    void show() { printf(">> "); inOrder(); printf("\n"); }
    void inOrder() const {
        if (root == nullptr) return;
        std::stack<Node*> S;
        Node* curr = root;
        while (curr != nullptr || !S.empty()) {
            while (curr != nullptr) {
                S.push(curr);
                curr = curr->left;
            }
            curr = S.top(); S.pop();
            printf("[%d]->", curr->data);
            curr = curr->right;
        }
    }
};
```

### Linked List

```cpp
#pragma once
#include <cstdio>
#include <stack>

template<typename T>
struct SingleNode {
    T data;
    SingleNode* next;
};

template<typename T>
struct sll_list_recur {
    using Node = SingleNode<T>;
    Node* head;

    sll_list_recur() { head = nullptr; }
    ~sll_list_recur() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    Node* find(const T& data) { return findRecur(data); }
    void insert(const T& data) { head = insertRecur(head, data); }
    void remove(const T& data) { head = removeRecur(head, data); }

    void clearRecur(Node* node) {
        // preorder deletion
        if (node == nullptr) return;
        Node* next = node->next;
        delete node;
        clearRecur(next);

        // preorder deletion
        //if (node == nullptr) return;
        //Node* temp = node;
        //node = node->next;
        //delete temp;
        //clearRecur(node);

        // postorder deletion
        //if (node == nullptr) return;
        //clearRecur(node->next);
        //delete node;
    }
    Node* findRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        return findRecur(node->next, data);
    }
    Node* insertRecur(Node* node, const T& data) {
        if (node == nullptr) return new Node{ data, nullptr };
        if (node->data == data) return node;    // No duplicates
        node->next = insertRecur(node->next, data);
        return node;
    }
    Node* removeRecur(Node* node, const T& data) {
        if (node == nullptr) return nullptr;
        if (node->data == data) {
            Node* temp = node;
            node = node->next;
            delete temp;
            return node;

            //Node* next = node->next;
            //delete node;
            //return next;
        }
        node->next = removeRecur(node->next, data);
        return node;
    }
    void show() {
        printf(">> ");
        preOrder(head);
        printf("\n");
    }
    void preOrder(Node* node) {
        if (node == nullptr) return;
        printf("[%d]->", node->data);
        preOrder(node->next);
    }
};

template<typename T>
struct sll_list_iter {
    using Node = SingleNode<T>;
    Node* head;

    sll_list_iter() { head = nullptr; }
    ~sll_list_iter() { clear(); }

    void clear() {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;

            //Node* temp = head;
            //head = head->next;
            //delete temp;
        }
    }
    Node* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return; // No duplicates
            prev = curr;
            curr = curr->next;
        }
        Node* newNode = new Node{ data, curr };
        if (prev == nullptr) head = newNode;
        else prev->next = newNode;
    }
    void remove(const T& data) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return; // No data

        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
    void show() {
        printf(">> ");
        preOrder();
        printf("\n");
    }
    void preOrder() {
        Node* curr = head;
        while (curr != nullptr) {
            printf("[%d]->", curr->data);
            curr = curr->next;
        }

        //if (head == nullptr) return;

        //std::stack<Node*> S;
        //S.push(head);
        //while (!S.empty()) {
        //    Node* node = S.top(); S.pop();
        //    if (node->next != nullptr) S.push(node->next);
        //    printf("[%d]->", node->data);
        //}
    }
};
```

### Priority Queue

```cpp
#pragma once

template<typename T>
struct pq_heap{
    T* heap;
    int heapSize;
    int capacity;

    pq_heap(int capacity = 100) { 
        heap = new T[capacity];
        heapSize = 0;
        this->capacity = capacity;
    }
    ~pq_heap() { delete[] heap; }

    void resize(int capacity) {
        T* newHeap = new T[capacity]; // Allocate new heap
        for (int i = 0; i < heapSize; i++) newHeap[i] = heap[i];
        delete[] heap; // Delete the old heap AFTER copying
        heap = newHeap;
        this->capacity = capacity;
    }
    void clear() { heapSize = 0; }
    void push(const T& data) { 
        if (heapSize == capacity) resize(capacity * 2);

        heap[heapSize] = data;
        siftUp(heapSize);
        heapSize++;
    }
    void pop() {
        heapSize--;
        swap(heap[0], heap[heapSize]);
        siftDown(0);
    }
    bool empty() { return heapSize == 0; }
    T top() { return heap[0];  }

private:
#if 1:
    // iterative methods
    void siftUp(int index) {
        int curr = index;
        int parent = (curr - 1) / 2; // parent index
        while (curr > 0) {
            if (heap[curr] < heap[parent]) break;

            swap(heap[curr], heap[parent]);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
    void siftDown(int index) {
        int curr = index;
        int child = 2 * curr + 1;    // left child index
        while (child < heapSize) {
            if (child + 1 < heapSize && heap[child] < heap[child + 1]) child++;
            if (heap[child] < heap[curr]) break;

            swap(heap[child], heap[curr]);
            curr = child;
            child = 2 * curr + 1;
        }
    }
#else
    // recursive methods
    void siftUp(int index) {
        if (index <= 0) return;         // base condition
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) return;

        swap(heap[index], heap[parent]);
        siftUp(parent);
    }
    void siftDown(int index) {
        int child = 2 * index + 1;      // left child index
        if (child >= heapSize) return;  // base condition
        if (child + 1 < heapSize && heap[child] < heap[child + 1]) child++;
        if (heap[child] < heap[index]) return;

        swap(heap[child], heap[index]);
        siftDown(child);
    }
#endif
    void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
};
```
