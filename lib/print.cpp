#include "linked_list.h"

#include <iostream>
#include <string>
#include <vector>

void print(std::vector<int> vec)
{
    int i = 0;
    for (int item : vec)
    {
        std::cout << i << ": " << item << '\n';
        i++;
    }
    std::cout << '\n';
}

void print(int val)
{
    std::cout << val << '\n';
    std::cout << '\n';
}

void print(ListNode &head)
{
    ListNode *current = &head;
    while (current != nullptr)
    {

        auto prevVal = current->prev == nullptr ? "nullptr" : std::to_string(current->prev->val);
        std::cout << "prev value: " << prevVal << '\n';
        std::cout << "value: " << current->val << '\n';
        std::string nextVal = current->next == nullptr ? "nullptr" : std::to_string(current->next->val);
        std::cout << "next value: " << nextVal << '\n';
        std::cout << '\n';
        current = current->next;
    }
}
