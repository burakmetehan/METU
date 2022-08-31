#include <iostream>

#include "BST.h"

template <class T>
char is_parent(BSTNode<T> * const parent, BSTNode<T> * const child) {
    if (parent->left == child)
        return 'L';
    else if (parent->right == child)
        return 'R';
    else
        return 0;        
}

using namespace std;

int main() {
    BST<int> tree;

    //tree.print(inorder);
    //tree.print(preorder);
    //tree.print(postorder);

    tree.insert(10);
    tree.insert(15);
    tree.insert(5);
    tree.insert(13);
    tree.insert(7);
    tree.insert(14);
    tree.insert(6);

    //tree.print(inorder);
    //tree.print(preorder);
    //tree.print(postorder);

    /* BST<int> tree2(tree);
    
    tree2.print(inorder);

    tree.print(preorder);
    tree2.print(preorder);

    tree.print(postorder);
    tree2.print(postorder);
    
    tree2.~BST();
    tree2.print(inorder);
 */
    
    
    
    tree.print(inorder);

    BSTNode<int>* ptr;
    
    cout << "Data: 6\n";
    ptr = tree.getSuccessor(tree.search(15), inorder);
    if (ptr) cout << "inorder succ: " << ptr->data << endl;
    else cout << "No inorder succ\n";

    ptr = tree.getSuccessor(tree.search(15), preorder);
    if (ptr) cout << "preorder succ: " << ptr->data << endl;
    else cout << "No preorder succ\n";

    ptr = tree.getSuccessor(tree.search(15), postorder);
    if (ptr) cout << "postorder succ: " << ptr->data << endl;
    else cout << "No postorder succ\n";
 
    return 0;
}
