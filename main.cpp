#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include <unordered_set>
class ListNode
{
public:
    int val{0};
    ListNode *next = NULL;
    ListNode *prev = NULL;
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

void printListValues(ListNode &head)
{
    ListNode *current = &head;
    int i = 0;
    while (current != NULL && i < 10)
    {

        std::string prevVal = current->prev == NULL ? "NULL" : std::to_string(current->prev->val);
        std::cout << "prev value: " << prevVal << '\n';
        std::cout << "value: " << current->val << '\n';
        std::string nextVal = current->next == NULL ? "NULL" : std::to_string(current->next->val);
        std::cout << "next value: " << nextVal << '\n';
        std::cout << '\n';
        current = current->next;
        i++;
    }
}

ListNode reverseListCopy(ListNode &node)
{
    ListNode *current = new ListNode(node.val);
    ListNode *future = node.next;
    while (future != NULL)
    {
        ListNode *last = new ListNode(current->val, *current->next);
        current = new ListNode(future->val, *last);
        future = future->next == NULL ? NULL : future->next;
    }
    return *current;
}

void reverseList(ListNode &node)
{
    ListNode *last = NULL;
    ListNode *current = &node;
    ListNode *future = node.next;
    while (future != NULL)
    {
        current->prev = current->next;
        current->next = last;
        last = current;
        current = future;
        future = future->next;
    }
    current->prev = current->next;
    current->next = last;
}

void insertSequentiallyIntoList(ListNode &head, int newVal)
{
    bool isDescending = head.val > head.next->val;
    bool isAscending = head.val < head.next->val;
    if ((isDescending && newVal > head.val) || (isAscending && newVal < head.val))
    {
        return;
    }
    ListNode *current = &head;
    ListNode *next = head.next;

    while (next != NULL)
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
    if (current->prev == NULL)
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

void setPreviousOnList(ListNode &head)
{
    ListNode *last = &head;
    ListNode *current = head.next;
    while (current != NULL)
    {
        current->prev = last;
        last = current;
        current = current->next;
    }
    head.prev = current;
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

ListNode buildDoublyLinkedList(std::vector<int> const vec)
{
    ListNode *prev = NULL;
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
    return *start;
}

std::vector<int> generateRandomIntVector(int length, int max)
{
    std::unordered_set<int> set{};
    for (int i = 0; i < length; i++)
    {
        int randNum = std::rand() % max;
        set.insert(randNum);
    }
    return std::vector(set.begin(), set.end());
}

void printVec(std::vector<int> vec)
{
    for (int item : vec)
    {
        std::cout << item << '\n';
    }
}

bool testQuickSort(std::vector<int> vec)
{
    for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        if (iter + 1 == vec.end())
        {
            break;
        }
        if (*iter > *(iter + 1))
        {
            return false;
        }
    }
    return true;
}

void quickSort(std::vector<int> vec, std::vector<int>::iterator start_iter, std::vector<int>::iterator end_iter, int count = 0)
{
    if (vec.size() <= 1 || count >= 250)
    {
        return;
    }
    // std::vector<int>::iterator l_iter = start_iter - 1;
    std::vector<int>::iterator p_iter = end_iter;
    // std::vector<int>::iterator r_iter = start_iter;
    int p_i = vec.size() - 1;
    int p_val = vec.at(p_i);
    std::cout << "p value: " << p_val << std::endl;
    int l_i = -1;
    int r_i = 0;
    int i{0};
    printVec(vec);
    while (l_i < r_i && i < 20)
    {
        i++;
        int l_val = l_i >= 0 ? vec.at(l_i) : -1;
        int r_val = vec.at(r_i);
        if (l_val > r_val)
        {
            int temp = l_val;
            vec.at(l_i) = r_val;
            vec.at(r_i) = temp;
            if (r_i < p_i)
            {
                r_i++;
            }
            l_i++;
            continue;
        }
        if (r_val > p_val && r_i < p_i)
        {
            r_i++;
            continue;
        }
        if (r_i < p_i)
        {
            r_i++;
        }
        l_i++;
    }
    std::cout << '\n';
    printVec(vec);
    // while (l_iter != r_iter && i < 200)
    // {
    //     i++;
    //     int l_val = *l_iter;
    //     int r_val = *r_iter;
    //     int p_val = *p_iter;
    //     if (r_val > p_val)
    //     {
    //         r_iter++;
    //         continue;
    //     }
    //     if (l_val >= r_val)
    //     {
    //         std::vector<int>::iterator temp_iter = r_iter;
    //         r_iter = l_iter;
    //         l_iter = temp_iter;
    //         if (p_iter != r_iter)
    //         {
    //             r_iter++;
    //         }
    //         l_iter++;
    //     }
}
// printVec(vec);
// quickSort(vec)

// std::vector<int> leftVec{};
// std::vector<int> rightVec{};
// for (std::vector<int>::iterator iter = vec.begin(); iter != l_iter; ++iter)
// {
//     leftVec.push_back(*iter);
// }
// for (std::vector<int>::iterator iter = r_iter; iter != vec.end(); ++iter)
// {
//     rightVec.push_back(*iter);
// }
// quickSort(leftVec, count + 1);
// quickSort(rightVec, count + 1);
// }

int main()
{
    // ListNode node5(50);
    // ListNode node4(40, node5);
    // ListNode node3(30, node4);
    // ListNode node2(20, node3);
    // ListNode node1(10, node2);

    std::vector<int> randIntVec = generateRandomIntVector(20, 100);
    std::vector<int>::iterator l_iter = randIntVec.begin();
    std::vector<int>::iterator r_iter = randIntVec.end() - 2;
    quickSort(randIntVec, l_iter, r_iter);
    // printVec(randIntVec);
    // std::cout << testQuickSort(randIntVec) << std::endl;

    return 0;
    std::vector<int> vec{10, 20, 30, 40, 50};
    ListNode head = buildDoublyLinkedList(vec);
    insertSequentiallyIntoList(head, 25);
    printListValues(head);

    // reverseList(node1);
    // setPreviousOnList(node5);
    // printListValues(node);
    return 0;
}
