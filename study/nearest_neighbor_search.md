### BST - 1

```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(NULL), right(NULL) {};
};

class BST {
private:
    Node* root;

public:
    BST() { root = NULL; }

    void insertNode(Node* node, int key);

    // Insert a new node with given value
    void insert(int key);
    // Find the value of the node with the closest key to target
    int findClosest(int target);
    void findClosestHelper(Node* node, int target, int& closestKey);

    // Remove the node with given value
    void remove(int key);
    Node* removeNode(Node* node, int key);
    int findMin(Node* node);
};

void BST::insert(int key) {
    if (root == NULL)
        root = new Node(key); // Create a new root node
    else
        insertNode(root, key); // Recursively call to insert into existing tree
}

void BST::insertNode(Node* node, int key) {
    if (key < node->key) {
        if (node->left == NULL)
            node->left = new Node(key); // Create a left child node
        else
            insertNode(node->left, key); // Recursively call to the left subtree
    }
    else if (key > node->key) {
        if (node->right == NULL)
            node->right = new Node(key); // Create a right child node
        else
            insertNode(node->right, key); // Recursively call to the right subtree
    }
}

int BST::findClosest(int target) {
    int closestKey = INT_MAX;
    findClosestHelper(root, target, closestKey);
    return closestKey;
}

void BST::findClosestHelper(Node* node, int target, int& closestKey) {
    if (node == NULL)
        return;

    if (abs(node->key - target) < abs(closestKey - target))
        closestKey = node->key; // Update the closest key
    else if (target < node->key)
        findClosestHelper(node->left, target, closestKey);
    else
        findClosestHelper(node->right, target, closestKey);
}

void BST::remove(int key) {
    root = removeNode(root, key); // Call to the helper function
}

Node* BST::removeNode(Node* node, int key) {
    if (node == NULL)
        return node;

    if (key < node->key)
        node->left = removeNode(node->left, key);
    else if (key > node->key)
        node->right = removeNode(node->right, key);
    else {
        // Node to be deleted has no children
        if (node->left == NULL && node->right == NULL) {
            delete node;
            return NULL; // Return NULL to indicate deletion
        }
        // Node to be deleted has one child
        else if (node->left == NULL)
            node = node->right;
        else if (node->right == NULL)
            node = node->left;
        // Node to be deleted has two children
        else {
            int minKey = findMin(node->right);
            node->key = minKey; // Replace key with in-order successor's key
            node->right = removeNode(node->right, minKey); // Remove the in-order successor
        }
    }
    return node;
}

int BST::findMin(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node->key; // Return the minimum key
}

int main() {
    BST bst;

    // Test insert function
    cout << "Insert 10, 20, 5, 15, 25" << endl;
    bst.insert(10);
    bst.insert(20);
    bst.insert(5);
    bst.insert(15);
    bst.insert(25);
    cout << "In-order traversal: ";
    cout << "10, 5, 20, 15, 25" << endl;

    // Test findClosest function
    cout << "Find closest key to 12: " << bst.findClosest(12) << endl; // Output: 10

    // Test remove function
    cout << "Remove 20:" << endl;
    bst.remove(20);
    cout << "In-order traversal after removal: ";
    cout << "5, 10, 15, 25" << endl;

    return 0;
}
```

### BST - 2

```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

public:
    BST() : root(nullptr) {}

    void insert(int key) {
        if (!root)
            root = new Node(key);
        else
            _insert_recursive(root, key);
    }

    void _insert_recursive(Node*& node, int key) {
        if (key < node->key) {
            if (!node->left)
                node->left = new Node(key);
            else
                _insert_recursive(node->left, key);
        }
        else if (key > node->key) {
            if (!node->right)
                node->right = new Node(key);
            else
                _insert_recursive(node->right, key);
        }
    }

    int findClosest(int target) {
        return _find_closest_recursive(root, target, root);
    }

    int _find_closest_recursive(Node* node, int target, Node* closest_node) {
        if (!node)
            return closest_node->key;

        if (abs(target - node->key) < abs(target - closest_node->key))
            closest_node = node;

        if (target < node->key)
            _find_closest_recursive(node->left, target, closest_node);
        else
            _find_closest_recursive(node->right, target, closest_node);

        return closest_node->key;
    }
};

int main() {
    BST bst;
    int keys[] = { 47, 91, 13, 72, 28, 85, 39, 94, 67, 41 };
    cout << "Inserting keys: ";
    for (int i : keys)
        bst.insert(i);
    cout << endl;

    int target;
    cout << "Enter target value: ";
    cin >> target;
    cout << "Closest value to target: " << bst.findClosest(target) << endl;

    return 0;
}
```


### STL map
```cpp
#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> bst;
    int keys[] = { 47, 91, 13, 72, 28, 85, 39, 94, 67, 41 };
    cout << "Inserting keys: ";
    for (int i : keys)
        bst[i] = 1; // 키를 삽입합니다
    cout << endl;

    int target;
    cout << "Enter target value: ";
    cin >> target;
    auto it = bst.lower_bound(target);
    if (it != bst.end())
        cout << "Closest value to target: " << (*it).first << endl;
    else {
        --it; // 이전 노드를 찾습니다
        int closest_value = abs((*it).first - target) < abs(((*bst.begin()).first) - target) ?
            (*it).first : (*bst.begin()).first;
        cout << "Closest value to target: " << closest_value << endl;
    }

    return 0;
}
```
