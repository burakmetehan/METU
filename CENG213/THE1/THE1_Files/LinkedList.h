#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void remove_node(Node<T> *node){
        if(!head) return; // head == NULL (empty list, size = 0)
        else if (size == 1)
        {
            delete node;
            head = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;

            if (node == head)
            {
                head = node->next;
            }
            else;

            delete node;
        }

        size--;
    }

    void insert_node(int index, T data){
        Node<T> *new_node;

        if(!head) // head == NULL (empty list)
        {
            new_node = new Node<T>(data);

            new_node->prev = new_node;
            new_node->next = new_node;

            head = new_node;
        }
        else if (index == 0 || index == size) // insert at the front or end 
        {
            new_node = new Node<T>(data, head->prev, head);

            new_node->prev->next = new_node;
            new_node->next->prev = new_node;

            if (!index) // index == 0
            {
                head = new_node;
            }
            else;
        }
        else // any index except front and end
        {
            Node<T> *index_node = getNodeAtIndex(index);

            new_node = new Node<T>(data, index_node->prev, index_node);

            new_node->prev->next = new_node;
            new_node->next->prev = new_node;
        }

        size++;
    }

    int contained_and_index(Node<T> *node) const
    {
        /* If there is such node, returning the index of it. Otherwise return -1. */
        if (!head) // head == NULL (list is empty)
        {
            return -1; // List is empty so no node
        }
        else
        {
            Node<T> *temp = head; // creating temp node to traverse
            int index = -1;
            bool contained = false; // return flag

            do
            {
                index++;

                if (temp == node)
                {
                    contained = true;
                    break;
                }

                temp = temp->next;
            } while (temp != head);
            
            return contained ? index : -1;
        }
    }

    void update_prev_next_nodes(Node<T> *node){
        node->prev->next = node;
        node->next->prev = node;
    }

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    // first initializations
    head = NULL;
    size = 0;

    if (obj.getFirstNode()) // the obj is not empty
    {
        Node<T> *temp = obj.getFirstNode(); // temp will be used to follow the obj instead of function call all for loop
        int i, obj_size = obj.getSize();

        for (i = 0; i < obj_size; i++)
        {
            insert_node(i, temp->data); // inserting other nodes

            temp = temp->next; // it is same with putting this expression as 3rd statement. This way it is more readable.
        }
    }
    else;
}

template<class T>
LinkedList<T>::~LinkedList() {
    removeAllNodes();
}

template<class T>
int LinkedList<T>::getSize() const {
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    return contained_and_index(node) != -1;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    if (head)
    {
        return head->prev;
    }
    else
    {
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    if (!head) // head == NULL
    {
        return NULL;
    }
    else
    {
        Node<T> *temp = head; // creating temp pointer to traverse
        bool existed = false; // whether there is such node or not

        do
        {
            if (temp->data == data)
            {
                existed = true;
                break;
            }

            temp = temp->next;
        } while (temp != head);
        
        return existed ? temp : NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    if (0 <= index && index < size) // index is not out of bounds
    {
        Node<T> *temp = head;

        while (index--)
        {
            temp = temp->next;
        }

        return temp;
    }
    else // index is out of bounds
    {
        return NULL;
    }
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    insert_node(0, data);
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    insert_node(size, data);
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    int index = contained_and_index(node); // getting index of node

    if (index != -1) // there is such node with index
    {
        insert_node(index+1, data);
    }
    else;
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    if (k < 2 || !head); // k<2 or empty list. Nothing will be done
    else
    {
        Node<T> *temp = head;
        int i;
        
        for(i = 1; i <= size+1; i++, temp = temp->next)
        {
            if (!(i%k)) // new_node needs to be inserted.
            {
                insert_node(i-1, data);
                
                i++; // i needs to be incremented by one more time due to the insertion of the new node
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    if (contained_and_index(node) != -1) // there is such node
    {
        remove_node(node);
    }
    else;    
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    if(!head) return; // head == NULL (empty list)
    else
    {
        Node<T> *temp;
        int i; // iteration count

        for (i = 0; i < size; i++)
        {
            temp = getNodeAtIndex(i);

            if (temp->data == data)
            {
                remove_node(temp);
                i--;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    if (head)
    {
        while (size)
        {
            remove_node(head);
        }
    }
    else;

    // Reseting the variables just in case
    head = NULL;
    size = 0;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    if (k < 2 || !head) return; // k<2 or empty list
    else
    {
        Node<T> *temp = head;
        int i = 1;

        do
        {
            temp = temp->next;

            if (!(i%k))
            {
                remove_node(temp->prev);
            }

            i++;
        } while (temp != head);
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    if(contained_and_index(node1) == -1 && contained_and_index(node2) == -1) // Nodes are not in list or list is empty
    {
        return;
    }
    else if (node1 == node2) // Nodes are same
    {
        return;
    }
    else if (size == 2) // There is only two nodes and there are going to be swapped. Therefore, it can be enough to just change the head.
    {
        head = head->next;
        return;       
    }
    else;

    // I will implement the function as if node1 is on left and node2 is on right. Therefore, if node2 is on left and node1 is on right, i need to change them. 
    if (node2->next == node1) // means that node2 is on left, to simplicity I will switch the nodes.
    {
        Node<T> *temp = node1;
        node1 = node2;
        node2 = temp;
    }
    else;

    // Copying current nodes info
    Node<T> 
    *node1_prev = node1->prev,
    *node1_next = node1->next,
    *node2_prev = node2->prev,
    *node2_next = node2->next;

    /* if (node1 == head && node2 == head->prev) // because of the switching above the nodes are switched
    {
        node1->prev = node1_next;
        node1->next = node2_next;
        node2->prev = node1_prev;
        node2->next = node2_prev;
    } */
    if ((node1->next == node2 && node2->prev == node1) || (node1->prev == node2 && node2->next == node1)) 
    // Nodes are consecutive. Same thing is checked but it is more likely to the first component of the or statement will be evaluated true if such a case happens.
    {
        // Swapping
        node1->prev = node1_next;
        node1->next = node2_next;
        node2->prev = node1_prev;
        node2->next = node2_prev;
    }
    else
    {
        node1->prev = node2_prev;
        node1->next = node2_next;
        node2->prev = node1_prev;
        node2->next = node1_next;
    }

    update_prev_next_nodes(node1);
    update_prev_next_nodes(node2);
 
    // Checking whether head needs to be changed or not. If it is needed, doing changing
    if (node1 == head)
    {
        head = node2;
    }
    else if (node2 == head)
    {
        head = node1;
    }
    else;
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    int i;

    for (i = 0; i < size; i++)
    {
        swap(getNodeAtIndex(i), getNodeAtIndex((i*i + seed) % size));
    }    
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    removeAllNodes();

    if (rhs.getFirstNode()) // rhs is not empty
    {
        Node<T> *temp = rhs.getFirstNode();
        int i, rhs_size = rhs.getSize();

        for (i = 0; i < rhs_size; i++)
        {
            insert_node(i, rhs.getNodeAtIndex(i)->data); // inserting other nodes

            temp = temp->next;
        }
    }
    else;

    return *this;
}

#endif //LINKEDLIST_H
