#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Insert a node into the BST
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Find the nearest point in the BST to a given target value
Node* findClosest(Node* root, int target) {
    Node* current = root;
    Node* closest = root; 
    int minDiff = abs(root->data - target);

    while (current != nullptr) {
        int diff = abs(current->data - target);
        if (diff < minDiff) {
            minDiff = diff;
            closest = current;
        }
        if (target < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return closest; 
}

int main() {
    Node* root = nullptr;

    // Populate the BST with sample data (you can change these values)
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 8);
    root = insert(root, 15);
    root = insert(root, 20);

    int target = 7;
    Node* nearestPoint = findClosest(root, target);
    std::cout << "Target: " << target << ", Nearest Point Value: " << nearestPoint->data << std::endl;


    return 0;
}