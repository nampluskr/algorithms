### BST

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
