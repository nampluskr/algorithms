#pragma once
#include <stack>

template<typename T>
struct singly_linked_list_iter {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    singly_linked_list_iter() { head = nullptr; }
    ~singly_linked_list_iter() { clear(); }

    // Iterative (Variation 1)
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    // Iterative (Variation 2)
    // void clear() {
    //     while (head != nullptr) {
    //         Node* next = head->next;
    //         delete head;
    //         head = next;
    //     }
    // }
    // Iterative (Stack)
    // void clear() {
    //     if (head == nullptr) return;
    //     std::stack<Node*> S;
    //     S.push(head);
    //     while (!S.empty()) {
    //         Node* curr = S.top(); S.pop();
    //         if (curr->next != nullptr) S.push(curr->next);
    //         delete curr;
    //     }
    //     head = nullptr;
    // }
    T* find(const T& data) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) return &curr->data;
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
};

template<typename T>
struct singly_linked_list_recur {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    singly_linked_list_recur() { head = nullptr; }
    ~singly_linked_list_recur() { clear(); }

    void clear() { clearRecur(head); head = nullptr; }
    T* find(const T& data) {
        Node* res = findRecur(head);
        return (res == nullptr) ? nullptr : &res->data;
    }
    void insert(const T& data) { head = insertRecur(head, data); }
    void remove(const T& data) { head = removeRecur(head, data); }

private:
    // Postorder
    void clearRecur(Node* node) {
        if (node == nullptr) return;
        clearRecur(node->next);
        delete node;    // postorder
    }
    // // Preorder (Variation 1)
    // void clearRecur(Node* node) {
    //     if (node == nullptr) return;
    //     Node* temp = node;
    //     node = node->next;
    //     delete temp     // preorder
    //     clearRecur(node);
    // }
    // // Preorder (Variation 2)
    // void clearRecur(Node* node) {
    //     if (node == nullptr) return;
    //     Node* next = node->next;
    //     delete node     // preorder
    //     clearRecur(next);
    // }
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
            // Variation 1
            Node* next = node->next;
            delete node;
            return next;

            // Variation 2
            // Node* temp = node;
            // node = node->next;
            // delete temp;
            // return node;
        }
        node->next = removeRecur(node->next, data);
        return node;
    }
};

template<typename T>
struct singly_linked_list_dummy {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

    singly_linked_list_dummy() { head = new Node{ {}, nullptr }; }
    ~singly_linked_list_dummy() { clear(); }

    void clear() {
        Node* curr = head->next;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head->next = nullptr;
    }
    T* find(const T& data) {
        Node* curr = head->next;
        while (curr != nullptr) {
            if (curr->data == data) return &curr->data;
            curr = curr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr) {
            if (curr->data == data) return; // No duplicates
            prev = curr;
            curr = curr->next;
        }
        prev->next = new Node{ data, curr };
    }
    void remove(const T& data) {
        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr) {
            if (curr->data == data) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return; // No data
        prev->next = curr->next;
        delete curr;
    }
};