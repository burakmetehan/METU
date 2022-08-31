#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;

    /*=================== Helper Functions ===================*/
    bool is_leaf(BSTNode<T>* node) const {
        return node->left == NULL && node->right == NULL;
    }

    bool contains_helper(const BSTNode<T>* const root, const BSTNode<T>* const node) const {
        if (!root)
            return false;

        if (root == node)
            return true;
        else if (node->data < root->data)
            return contains_helper(root->left, node);
        else if (node->data > root->data)
            return contains_helper(root->right, node);
        else // The erroneous test. pointer is not same with node but data is same
            return false;
    }

    void copy_tree(BSTNode<T>* &root, const BSTNode<T>* const obj) {
        if (obj == NULL)
        {
            root = NULL;
            return;
        }
        
        root = new BSTNode<T>(obj->data, NULL, NULL);
        
        copy_tree(root->left, obj->left);
        copy_tree(root->right, obj->right);
    }

    void insert_helper(BSTNode<T>* &root, const T &data) {
        if (!root) // root == NULL
            root = new BSTNode<T>(data, NULL, NULL);
        else if (data < root->data) // left insert
            insert_helper(root->left, data);
        else if (data > root->data) // right insert
            insert_helper(root->right, data);
        else; // duplicate
    }
    
    void remove_helper(BSTNode<T>* &root, const T &data) {
        if (!root) // root == NULL
            return;
        
        /* 
        It should be guaranteed that there is a node that contains data in binary tree whose root is root 
        rm = remove_node
        rmp = remove_node_parent
        rp = replace_node
        rpp = replace_node_parent
        */
        BSTNode<T> *rm, *rmp;

        rm = find_node(root, data); // Finding the node that will be deleted

        if (!rm) // node is not found, no deletion
            return;
        else if (rm == root)
            rmp = NULL;
        else
            rmp = find_parent(root, rm);
        
        if (is_leaf(rm)) // Node that will be deleted is a leaf
        {
            if (!rmp) // Tree has 1 node, rm == root
                root = NULL;
            else if (rmp->left == rm)
                rmp->left = NULL;
            else
                rmp->right = NULL;
            
            delete rm;
        }
        else if (rm->left && rm->right) // Node that will be deleted has 2 subtrees
        {
            /* Minimum of the right subtree needs to be switched with the given node which is the inorder successor of the node. It can be achieved the following way:
                1. Find the inorder successor
                2. Save the data of the successor
                3. Delete successor
                4. Change the value of remove_node                            
            */
            BSTNode<T> *successor = find_min_node(rm->right);
            T succ_data = successor->data;

            remove_helper(root, succ_data);

            rm->data = succ_data;
        }
        else // Node that will be deleted has 1 subtree
        {
            if (rm->left)
            {
                if (!rmp) // rmp == NULL / rm == root / root will be deleted
                    root = rm->left;
                else if (rmp->left == rm)
                    rmp->left = rm->left;
                else
                    rmp->right = rm->left;
            }
            else
            {
                if (!rmp) // rmp == NULL / rm == root / root will be deleted
                    root = rm->right;
                else if (rmp->left == rm)
                    rmp->left = rm->right;
                else
                    rmp->right = rm->right;
            }

            delete rm;
        }
    }

    void removeAll_helper(BSTNode<T>* &root) {
        if (!root) // root == NULL 
            return;

        removeAll_helper(root->left);
        removeAll_helper(root->right);

        delete root;
        root = NULL;
    }

    BSTNode<T> *find_node(BSTNode<T>* const root, const T &data) const {
        if (!root) // tree is empty or node is not found
            return NULL;
        
        if (data == root->data)
            return root;
        else if (data < root->data)
            return find_node(root->left, data);
        else // data > root->data
            return find_node(root->right, data);
    }

    BSTNode<T>* find_parent(BSTNode<T>* const root, const BSTNode<T>* const child_node) const {
        /* It should be guaranteed that child_node is not NULL and root is not same with child_node 
            - child_node != NULL
            - root != child_node
        */
        if (!root) // root == NULL. The child_node is not in binary tree
            return NULL;
        
        if (root->left == child_node || root->right == child_node)
            return root;
        else if (child_node->data < root->data)
            return find_parent(root->left, child_node);
        else if (child_node->data > root->data)
            return find_parent(root->right, child_node);
        else
            return NULL;
    }

    BSTNode<T>* find_min_node(BSTNode<T>* const root) const {
        if (!root) // root == NULL
            return NULL;
        
        if (root->left)
            return find_min_node(root->left);
        else
            return root;
    }

    /*=========== Helpers of getSuccessor function ===========*/
    // These functions return the successor for special cases.
    BSTNode<T>* inorder_successor(BSTNode<T>* const root, const BSTNode<T>* const node, BSTNode<T>* successor=NULL) const {
        // It should be guaranteed that node and root are not NULL and node is on tree.
        if (node->data == root->data)
            return successor;
        else if (node->data < root->data)
        {
            successor = root;

            return inorder_successor(root->left, node, successor);
        }
        else // node->data > root->data
            return inorder_successor(root->right, node, successor);
    }

    BSTNode<T>* preorder_successor(BSTNode<T>* const root, const BSTNode<T>* const node, BSTNode<T>* successor=NULL) const {
        // It should be guaranteed that node and root are not NULL and node is on tree.
        if (node->data == root->data)
            return successor;
        else if (node->data < root->data)
        {
            if (root->right)
                successor = root->right;

            return preorder_successor(root->left, node, successor);
        }
        else // node->data > root->data
            return preorder_successor(root->right, node, successor);
    }

    BSTNode<T>* postorder_successor(BSTNode<T>* const subtree_root) const {
        // It should be guaranteed that node and root are not NULL and node is on tree.
        if (is_leaf(subtree_root))
            return subtree_root;
        else if(subtree_root->left)
            return postorder_successor(subtree_root->left);
        else
            return postorder_successor(subtree_root->right);
    }
    /*========================================================*/

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    root = NULL;
    
    if (obj.getRoot()) // obj.root == NULL
        copy_tree(root, obj.getRoot());
}

template<class T>
BST<T>::~BST() {
    removeAllNodes();
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    return root == NULL;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    if (!root || !node) // root == NULL or node == NULL
        return false;
    else
        return contains_helper(root, node);
}

template<class T>
void BST<T>::insert(const T &data) {
    insert_helper(root, data);
}

template<class T>
void BST<T>::remove(const T &data) {
    remove_helper(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    removeAll_helper(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    return find_node(root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    if (!root || !node || !contains(node))
        return NULL;

    if (tp == inorder)
    {
        /*
        - If the node has right child, successor is node->right
        - If the node does not have right child, helper is needed
        */
        if (node->right)
            return find_min_node(node->right);
        else
            return inorder_successor(root, node);
    }
    else if (tp == preorder)
    {
        /* 
        - If the node has left node, successor is node->left
        - If the node does not have left node but has right node, successor is node-> right
        - If the node does not have left node and right node helper is needed
        */
        if (node->left)
            return node->left;
        else if (node->right)
            return node->right;
        else
            return preorder_successor(root, node);
    }
    else if (tp == postorder)
    {
        /*
        - If the node is the right child of its parent, successor is its parent

        - If the node is the left child and there is right subtree of its parent, successor is the right subtree's leaf that has the min value. That is, it is needed to find the minimum valued "leaf" of the right subtree of the parent of given node

        - If the node is the left child and there is not right subtree of its parent, successor is the parent
        */
        BSTNode<T>* parent = find_parent(root, node);

        if (!parent) // given node is root, no parent
            return NULL;
        else if (node == parent->right)
            return parent;
        else if (parent->right)
            return postorder_successor(parent->right);
        else
            return parent;
    }
    else
        return NULL;
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder)
    {
        if (isEmpty()) // tree is empty
            std::cout << "BST_inorder{}" << std::endl;
        else
        {
            std::cout << "BST_inorder{" << std::endl;
            print(root, inorder);
            std::cout << std::endl << "}" << std::endl;
        }
    }
    else if (tp == preorder)
    {
        if (isEmpty()) // tree is empty
            std::cout << "BST_preorder{}" << std::endl;
        else
        {
            std::cout << "BST_preorder{" << std::endl;
            print(root, preorder);
            std::cout << std::endl << "}" << std::endl;
        }  
    }
    else if (tp == postorder)
    {
        if (isEmpty()) // tree is empty
            std::cout << "BST_postorder{}" << std::endl;
        else
        {
            std::cout << "BST_postorder{" << std::endl;
            print(root, postorder);
            std::cout << std::endl << "}" << std::endl;
        }  
    }
    else;
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    removeAllNodes();
    copy_tree(root, rhs.getRoot());
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {
    if (!node) // node == NULL
        return;

    if (tp == inorder)
    {
        /* inorder: left, root, right */

        // left
        print(node->left, inorder); 
        if (node->left) // comma if it is needed
            std::cout << "," << std::endl;

        // root
        std::cout << "\t" << node->data;

        // right
        if (node->right) // comma if it is needed
            std::cout << "," << std::endl;
        print(node->right, inorder);
    }
    else if (tp == preorder)
    {
        /* preorder: root, left, right */

        // root
        std::cout << "\t" << node->data;

        // left
        if (node->left) // comma if it is needed
            std::cout << "," << std::endl;
        print(node->left, preorder);

        // right
        if (node->right) // comma if it is needed
            std::cout << "," << std::endl;
        print(node->right, preorder);
    }
    else if (tp == postorder)
    {
        /* postorder: left, right, root */

        // left
        print(node->left, postorder);
        if (node->left) // comma if it is needed
            std::cout << "," << std::endl;

        // right
        print(node->right, postorder);
        if (node->right) // comma if it is needed
            std::cout << "," << std::endl;

        // root
        std::cout << "\t" << node->data;
    }
    else;
}
