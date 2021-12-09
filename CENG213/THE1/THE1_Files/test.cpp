#include <iostream>

#include "LinkedList.h"
#include "MusicStream.h"

using namespace std;

template <class T>
void print(T print_value)
{
    cout << print_value << endl;
}



void test_swap(){
    for (int i=0; i < 4; i++)
    {
        for (int j=0; j < 4; j++)
        {
            LinkedList<int> list;

            list.insertAtTheFront(1);
            list.insertAtTheEnd(2);
            list.insertAtTheEnd(3);
            list.insertAtTheEnd(4);

            list.swap(list.getNodeAtIndex(i), list.getNodeAtIndex(j));

            list.print();

            list.~LinkedList();
        }
    }
}

void test_addSong(){
    Album album1;
    cout << album1.getName();
}

int main(){
    test_addSong();


    //test_swap();
    /* LinkedList<int> list;
    LinkedList<int> new_list;

    list.print();

    list = new_list;
    list.print();

    new_list.insertAtTheEnd(1);
    list = new_list;
    list.print();

    list.insertAtTheFront(1);
    list.insertAtTheEnd(2);
    list.insertAtTheEnd(3);
    list.insertAtTheEnd(4);
    list.insertAtTheEnd(5);
    list.insertAtTheEnd(6);
 */
    /* Node<int> *test_node = new Node<int>(5);
    test_node->prev = test_node;
    test_node->next = test_node;

    print(list.getSize());
    print(list.isEmpty());
    print(list.contains(NULL));
    print(list.contains(test_node));
    print(list.getFirstNode());
    print(list.getLastNode());
    print("--------");
    print(list.getNode(5));
    print("*******");
    print(list.getNodeAtIndex(0));
    print(list.getNodeAtIndex(1));
 */
/*     print("Before:");
    list.print();

    list = new_list;
    print("After copy empty list = operator");
    list.print();

    new_list.insertAtTheEnd(9);
    new_list.insertAtTheEnd(10);
    new_list.insertAtTheEnd(11);
    new_list.insertAtTheEnd(12);
    new_list.insertAtTheEnd(13);
    new_list.insertAtTheEnd(14);
    new_list.insertAtTheEnd(15);
    new_list.insertAtTheEnd(16);
    new_list.insertAtTheEnd(17);

    list = new_list;
    print("After copy list = operator");
    list.print();
 */
    return 0;
}
