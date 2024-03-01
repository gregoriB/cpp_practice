#pragma once
#include <iostream>
#include <vector>

class ListNode
{
  public:
    ListNode *next;
    ListNode *prev;
    int val;

    ListNode(int value);
    ListNode(int value, ListNode &nextNode);
    ListNode(int value, ListNode &nextNode, ListNode &prevNode);
};

void reverseLinkedList(ListNode &head);
ListNode &getLastNode(ListNode head, std::string direction);
ListNode findNodeByValue(const ListNode head, int val);
void insertIntoOrderedLinkedList(ListNode &head, int newVal);
void setPreviousOnList(ListNode &head);
void deleteFromList(ListNode &head, int val);
ListNode buildDoublyLinkedList(std::vector<int> vec);
ListNode getMiddleNode(ListNode &head);
void runLinkedListTests(std::vector<int> numbers);
