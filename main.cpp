#include "lib/binary_tree.h"
#include "lib/linked_list.h"
#include "lib/quick_sort.h"

#include <unordered_set>
#include <vector>

auto generateRandomIntVector(int length, int max)
{
    std::unordered_set<int> set{};
    while (set.size() < std::size_t(length))
    {
        int randNum = (std::rand() % max) + 1;
        set.insert(randNum);
    }
    return std::vector(set.begin(), set.end());
}

void runBinaryTreeTests()
{
    std::vector<int> vec{56, 68, 34, 45, 74, 86, 62, 39, 21};
    testBuildBinaryTree(vec);
}

void runTests()
{
    int vec_len{20000};
    int max_int_val{100000};
    auto rand_numbers = generateRandomIntVector(vec_len, max_int_val);

    runQuickSortTests(rand_numbers);

    auto numbers = rand_numbers;
    quickSort(numbers);

    runLinkedListTests(numbers);
    runBinaryTreeTests();
}

int main()
{
    runTests();
    return 0;
}
