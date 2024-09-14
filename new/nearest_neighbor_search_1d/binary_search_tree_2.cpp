// Gemimi
#if 0
#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* newNode(int item) {
    Node* node = new Node();
    node->key = item;
    node->left = node->right = nullptr;
    return node;
}

// 이진 탐색 트리에 노드 삽입
Node* insert(Node* node, int key) {
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

// 타겟 값과 가장 가까운 값 찾기
int findClosest(Node* root, int target) {
    Node* current = root;
    int closest = root->key;

    while (current != nullptr) {
        if (target == current->key) {
            return target;
        } else if (target < current->key) {
            closest = current->key; // 현재 노드의 값을 임시로 가장 가까운 값으로 설정
            current = current->left;
        } else {
            closest = current->key;
            current = current->right;
        }
    }

    return closest;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 18);

    int target = 15;
    std::cout << "Closest value to " << target << " is: "
              << findClosest(root, target) << std::endl;

    return 0;
}
#endif