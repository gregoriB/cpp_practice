#include <iostream>
#include <string>
#include <vector>

class ListNode
{
  public:
    int val{0};
    ListNode *next = nullptr;
    ListNode *prev = nullptr;
    ListNode(int value)
    {
        val = value;
    };
    ListNode(int value, ListNode &nextNode)
    {
        next = &nextNode;
        val = value;
    };
    ListNode(int value, ListNode &nextNode, ListNode &prevNode)
    {
        next = &nextNode;
        prev = &prevNode;
        val = value;
    };
};

void reverseLinkedList(ListNode &head)
{
    head.prev->next = &head;
    head.prev = nullptr;
    ListNode *last = head.prev;
    ListNode *future = head.next;
    ListNode *current = &head;
    while (future != nullptr)
    {
        current->prev = future;

        current->next = last;

        last = current;
        current = future;
        future = future->next;
    }
}

ListNode &getLastNode(ListNode head, std::string direction)
{
    ListNode *temp = &head;
    if (direction == "forward")
    {
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
    }
    else
    {
        while (temp->prev->next != nullptr)
        {
            temp = temp->prev;
        }
    }
    ListNode *lastNode{temp};
    return *lastNode;
}

void testReverseLinkedList(ListNode head)
{
    ListNode original = getLastNode(head, "forward");
    reverseLinkedList(head);
    ListNode reversed = getLastNode(head, "reverse");
    while (reversed.prev->next != nullptr)
    {
        if (reversed.val != original.val)
        {
            std::cout << "Failed Reverse List " << reversed.val << " does not equal " << original.val << '\n';
            return;
        }
        original = *original.prev;
        reversed = *reversed.prev;
    }
    std::cout << "Passed Reverse List\n";
}

void insertIntoOrderedLinkedList(ListNode &head, int newVal)
{
    bool isDescending = head.val > head.next->val;
    bool isAscending = head.val < head.next->val;
    if ((isDescending && newVal > head.val) || (isAscending && newVal < head.val))
    {
        return;
    }
    ListNode *current = &head;
    ListNode *next = head.next;

    while (next != nullptr)
    {
        int c = current->val;
        int n = next->val;
        bool isBetween = (newVal > c && newVal < n) || (newVal < c && newVal > n);
        if (isBetween)
        {
            break;
        }
        current = next;
        next = current->next;
    }
    if (current->prev == nullptr)
    {
        ListNode *newNode = new ListNode(newVal, *current->next);
        current->next = newNode;
    }
    else
    {
        ListNode *newNode = new ListNode(newVal, *current->next, *current);
        newNode->next->prev = newNode;
        current->next = newNode;
    }
}

ListNode findNodeByValue(const ListNode head, int val)
{
    ListNode current = head;
    while (current.next != nullptr)
    {
        if (current.val == val)
        {
            return current;
        }
        current = *current.next;
    }
    return current;
}

void testInsertSequentiallyIntoOrderedLinkedList(ListNode head, int val)
{
    insertIntoOrderedLinkedList(head, val);
    ListNode newNode = findNodeByValue(head, val);
    int prevVal = newNode.prev->val;
    int nextVal = newNode.next->val;
    if (nextVal < val)
    {
        std::cout << "Failed Sequential Insert Ascending"
                  << " Next value: " << nextVal << " Current value: " << newNode.val << '\n';
        return;
    }
    if (prevVal > val)
    {
        std::cout << "Failed Sequential Insert Ascending"
                  << " Prev value: " << prevVal << " Current value: " << newNode.val << '\n';
        return;
    }
    std::cout << "Passed Sequential Insert Ascending\n";
}

void setPreviousOnList(ListNode &head)
{
    ListNode *last = &head;
    ListNode *current = head.next;
    while (current != nullptr)
    {
        current->prev = last;
        last = current;
        current = current->next;
    }
    head.prev = current;
}

void testSetPreviousOnList(ListNode head)
{
    setPreviousOnList(head);
    ListNode *current = head.next;
    while (current != nullptr)
    {
        if (current->prev == nullptr)
        {
            std::cout << "Failed Set Previous on List\n";
            return;
        }
        current = current->next;
    }
    std::cout << "Passed Set Previous on List\n";
}

void deleteFromList(ListNode &head, int val)
{
    ListNode *current = head.next;
    while (current != nullptr)
    {
        if (current->val == val)
        {
            current->prev->next = current->next;
            if (current->next != nullptr)
            {
                current->next->prev = current->prev;
            }
            break;
        }
        current = current->next;
    }
}

void testDeleteFromList(std::vector<int> numbers, ListNode head)
{
    auto iter = numbers.end();
    iter += numbers.size() / 2;
    auto val_to_remove = *iter;
    deleteFromList(head, val_to_remove);
    ListNode *current = head.next;
    while (current != nullptr)
    {
        if (current->val == val_to_remove)
        {
            std::cout << "Failed Set Previous on List\n";
            return;
        }
        current = current->next;
    }
    std::cout << "Passed Set Previous on List\n";
}

ListNode buildDoublyLinkedList(std::vector<int> vec)
{
    ListNode *prev = nullptr;
    ListNode *start = new ListNode(*vec.begin());
    ListNode *head = start;
    for (auto iter = vec.begin() + 1; iter != vec.end(); ++iter)
    {
        ListNode *temp = new ListNode(*iter);
        prev = head;
        temp->prev = prev;
        head->next = temp;
        head = temp;
    }
    head->next = nullptr;
    start->prev = head;
    return *start;
}

void testBuildDoublyLinkedList(std::vector<int> vec)
{
    auto head = buildDoublyLinkedList(vec);
    auto *c = &head;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        if (c->val != *(it) || (c->prev == nullptr && *it != 10))
        {
            std::cout << "Failed Build Doubly Linked List " << c->val << " does not equal " << *it << '\n';
            return;
        }
        c = c->next;
    }
    std::cout << "Passed Build Doubly Linked List\n";
}
