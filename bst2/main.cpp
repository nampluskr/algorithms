#include "bst2.h"

template<typename T>
void testBST(T& bst) {
    bst.clear(); bst.show();

    bst.insert(20);
    bst.insert(50);
    bst.insert(40);
    bst.insert(10);
    bst.insert(30);
    bst.insert(20);
    bst.show();

    bst.remove(20); bst.show();
    bst.remove(30); bst.show();
    bst.remove(10); bst.show();
    bst.remove(50); bst.show();

    bst.clear(); bst.show();
}

int main()
{
    BinarySearchTree bst1(new BSTRecur());
    BinarySearchTree bst2(new BSTIter());

    testBST(bst1);
    testBST(bst2);
    
    return 0;
}