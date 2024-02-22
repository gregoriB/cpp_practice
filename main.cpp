#include <iostream>
#include <string>
#include <unordered_set>
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

        std::string prevVal = current->prev == nullptr ? "nullptr" : std::to_string(current->prev->val);
        std::cout << "prev value: " << prevVal << '\n';
        std::cout << "value: " << current->val << '\n';
        std::string nextVal = current->next == nullptr ? "nullptr" : std::to_string(current->next->val);
        std::cout << "next value: " << nextVal << '\n';
        std::cout << '\n';
        current = current->next;
    }
}

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

ListNode *getLastNode(ListNode head, std::string direction)
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
    return lastNode;
}

void testReverseLinkedList(ListNode head)
{
    ListNode *original = getLastNode(head, "forward");
    reverseLinkedList(head);
    ListNode *reversed = getLastNode(head, "reverse");
    while (reversed->prev->next != nullptr)
    {
        if (reversed->val != original->val)
        {
            std::cout << "Failed Reverse List " << reversed->val << " does not equal " << original->val << '\n';
            return;
        }
        original = original->prev;
        reversed = reversed->prev;
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

ListNode buildLinkedList(std::vector<int> const vec)
{
    ListNode *end = new ListNode(vec[vec.size() - 1]);
    ListNode *head = end;
    for (double i = double(vec.size()) - 2; i >= 0; --i)
    {
        ListNode *temp = new ListNode(vec[size_t(i)], *head);
        head = temp;
    }
    return *head;
}

void testBuildLinkedList()
{
    std::vector<int> vec{10, 20, 30, 40, 50};
    ListNode current = buildLinkedList(vec);
    ListNode *c = &current;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        if (c->val != *it)
        {
            std::cout << "Failed Build Linked List " << c->val << " does not equal " << *it << '\n';
            return;
        }
        c = c->next;
    }
    std::cout << "Passed Build Linked List\n";
}

ListNode buildDoublyLinkedList(std::vector<int> const vec)
{
    ListNode *prev = nullptr;
    ListNode *start = new ListNode(vec[0]);
    ListNode *head = start;
    for (double i = 1; i < double(vec.size()); ++i)
    {
        ListNode *temp = new ListNode(vec[size_t(i)]);
        prev = head;
        temp->prev = prev;
        head->next = temp;
        head = temp;
    }
    start->prev = head;
    return *start;
}

void testBuildDoublyLinkedList()
{
    std::vector<int> vec{10, 20, 30, 40, 50};
    ListNode head = buildDoublyLinkedList(vec);
    ListNode *c = &head;
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

std::vector<int> generateRandomIntVector(int length, int max)
{
    std::unordered_set<int> set{};
    for (int i = 0; i < length; i++)
    {
        int randNum = (std::rand() % max) + 1;
        set.insert(randNum);
    }
    return std::vector(set.begin(), set.end());
}

void quickSort(std::vector<int> &vec)
{
    if (!vec.size())
    {
        return;
    }
    std::vector<int>::iterator p = vec.end() - 1;
    std::vector<int>::iterator i = vec.begin() - 1;
    std::vector<int>::iterator j = vec.begin();
    while (i != p - 1)
    {
        if (*j > *p)
        {
            ++j;
            continue;
        }
        else if (*i > *j)
        {
            int temp{*j};
            *j = *i;
            *i = temp;
        }
        else
        {
            ++i;
        }

        if (j == p)
        {
            vec.insert(i + 1, *p);
            vec.pop_back();
            p = vec.end() - 1;
            i = vec.begin() - 1;
            j = vec.begin();
            continue;
        }
        ++j;
    }
}

void testQuickSort(std::vector<int> vec)
{
    quickSort(vec);
    for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        std::vector<int>::iterator next_iter = iter + 1;
        if (next_iter == vec.end())
        {
            break;
        }
        if (*iter > *(next_iter))
        {
            std::cout << "Failed Quick Sort " << *iter << " is greater than " << *(next_iter) << '\n';
            return;
        }
    }
    std::cout << "Passed Quick Sort \n";
}

int main()
{
    // Quick sort
    int vec_len{20000};
    int max_int{100000};
    std::vector<int> randIntVec = generateRandomIntVector(vec_len, max_int);
    std::cout << "Sorting... " << std::endl;
    testQuickSort(randIntVec);

    testBuildLinkedList();
    testBuildDoublyLinkedList();
    std::vector<int> vec{10, 20, 30, 40, 50};
    ListNode head = buildDoublyLinkedList(vec);
    testInsertSequentiallyIntoOrderedLinkedList(head, 25);

    testSetPreviousOnList(head);
    testReverseLinkedList(head);
    return 0;
}
