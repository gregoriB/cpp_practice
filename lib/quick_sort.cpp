#include <iostream>
#include <vector>

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
