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
void testReverseLinkedList(ListNode head);

ListNode &getLastNode(ListNode head, std::string direction);
ListNode findNodeByValue(const ListNode head, int val);

void insertIntoOrderedLinkedList(ListNode &head, int newVal);
void testInsertSequentiallyIntoOrderedLinkedList(ListNode head, int val);

void setPreviousOnList(ListNode &head);
void testSetPreviousOnList(ListNode head);

void deleteFromList(ListNode &head, int val);
void testDeleteFromList(std::vector<int> numbers, ListNode head);

ListNode buildDoublyLinkedList(std::vector<int> vec);
void testBuildDoublyLinkedList(std::vector<int> vec);
