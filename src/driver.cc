#include <iostream>

#include "circular-linked-list.hpp"

int main() {
    CircularLinkedList<int> list;
    list.InsertInOrder(1);
    list.InsertInOrder(3);
    list.InsertInOrder(2);
    CircularLinkedList<int> list2;
    list2 = list;
    list2.Reverse();
}
