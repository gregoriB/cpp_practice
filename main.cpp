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

        auto prevVal = current->prev == nullptr ? "nullptr" : std::to_string(current->prev->val);
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

auto generateRandomIntVector(int length, int max)
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
    auto p = vec.end() - 1;
    auto l = vec.begin() - 1;
    auto r = vec.begin();
    while (l != p - 1)
    {
        if (*r > *p)
        {
            ++r;
            continue;
        }
        else if (*l > *r)
        {
            int temp{*r};
            *r = *l;
            *l = temp;
        }
        else
        {
            ++l;
        }

        if (r == p)
        {
            vec.insert(l + 1, *p);
            vec.pop_back();
            p = vec.end() - 1;
            l = vec.begin() - 1;
            r = vec.begin();
            continue;
        }
        ++r;
    }
}

void testQuickSort(std::vector<int> vec)
{
    quickSort(vec);
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        auto next_iter = iter + 1;
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

void runTests()
{
    int vec_len{20000};
    int max_int_val{100000};
    auto rand_numbers = generateRandomIntVector(vec_len, max_int_val);

    std::cout << "Sorting... " << std::endl;
    testQuickSort(rand_numbers);

    auto numbers = rand_numbers;
    quickSort(numbers);

    testBuildDoublyLinkedList(numbers);

    ListNode head = buildDoublyLinkedList(numbers);
    testInsertSequentiallyIntoOrderedLinkedList(head, 25);

    head = buildDoublyLinkedList(numbers);
    testSetPreviousOnList(head);

    head = buildDoublyLinkedList(numbers);
    testReverseLinkedList(head);
}

int main()
{
    runTests();
    return 0;
}
