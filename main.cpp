#include <iostream>
#include <string>
#include <vector>
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
        int randNum = (std::rand() % max) + 1;
        set.insert(randNum);
    }
    return std::vector(set.begin(), set.end());
}

void printVec(std::vector<int> vec)
{
    int i = 0;
    for (int item : vec)
    {
        std::cout << i << ": " << item << '\n';
        i++;
    }
}

void printInt(int val) 
{
  std::cout << val << " ";
}

bool testQuickSort(std::vector<int> vec)
{
    for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        std::vector<int>::iterator next_iter = iter + 1;
        if (next_iter == vec.end())
        {
            break;
        }
        if (*iter > *(next_iter))
        {
            return false;
        }
    }
    return true;
}

void quickSort(std::vector<int> &vec)
{
    if (vec.size() <= 1)
    {
        return;
    }

    std::vector<int>::iterator i_iter = vec.begin() - 1;
    std::vector<int>::iterator j_iter = vec.begin();
    std::vector<int>::iterator p_iter = vec.end() - 1;
    while (j_iter != vec.end() && i_iter != vec.end()) {
      int i = *i_iter;
      int j = *j_iter;
      int p = *p_iter;
      if (j_iter == p_iter && i_iter == p_iter - 1) 
      {
        break;
      }
      if (j_iter == p_iter) 
      {
        vec.insert(++i_iter, p);
        vec.pop_back();
        p_iter = vec.end() - 1;
        i_iter = vec.begin() -1;
        j_iter = vec.begin();
        continue;
      }
      if (j < p) 
      {
        i = *(++i_iter);
        if (i > j) 
        {
          int temp = j;
          *j_iter = i;
          *i_iter = temp;
        }
      }
      j_iter++;
    }
}

int main()
{
    // ListNode node5(50);
    // ListNode node4(40, node5);
    // ListNode node3(30, node4);
    // ListNode node2(20, node3);
    // ListNode node1(10, node2);

    std::vector<int> randIntVec = generateRandomIntVector(20, 10);
    quickSort(randIntVec);

    std::cout << "Passed? ... " << testQuickSort(randIntVec) << '\n';

    return 0;
    std::vector<int> vec{10, 20, 30, 40, 50};
    ListNode head = buildDoublyLinkedList(vec);
    insertSequentiallyIntoList(head, 25);
    //printListValues(head);

    // reverseList(node1);
    // setPreviousOnList(node5);
    // printListValues(node);
    return 0;
}
