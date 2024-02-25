#include "lib/linked_list.h"
#include "lib/quick_sort.h"

#include <iostream>
#include <unordered_set>
#include <vector>

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
    testDeleteFromList(numbers, head);

    head = buildDoublyLinkedList(numbers);
    testReverseLinkedList(head);
}

int main()
{
    runTests();
    return 0;
}
