#include <iostream>
#include <vector>

class TreeNode
{
  public:
    int val{0};
    TreeNode *right = nullptr;
    TreeNode *left = nullptr;
    TreeNode(int value)
    {
        val = value;
    };
};

void print(const TreeNode node)
{
    std::cout << "value: " << node.val << '\n';
    if (node.left != nullptr)
    {
        print(*node.left);
    }
    if (node.right != nullptr)
    {
        print(*node.right);
    }
}

void print()
{
    std::cout << '\n';
}

TreeNode insertIntoTree(TreeNode &head, int val)
{
    if (val > head.val)
    {
        if (head.right == nullptr)
        {
            TreeNode *temp = new TreeNode(val);
            head.right = temp;
            return *temp;
        }
        else
        {
            return insertIntoTree(*head.right, val);
        }
    }
    if (val < head.val)
    {
        if (head.left == nullptr)
        {
            TreeNode *temp = new TreeNode(val);
            head.left = temp;
            return *temp;
        }
        else
        {
            return insertIntoTree(*head.left, val);
        }
    }
    return head;
}

TreeNode buildBinaryTree(std::vector<int> vec)
{
    TreeNode *head = new TreeNode(*vec.begin());
    for (auto iter = vec.begin() + 1; iter != vec.end(); ++iter)
    {
        insertIntoTree(*head, *iter);
    }
    return *head;
}

TreeNode findTreeNode(const TreeNode &head, int val)
{
    TreeNode start = head;
    while (start.left != nullptr || start.right != nullptr)
    {
        if (start.val == val)
        {
            break;
        }

        start = val > start.val ? *start.right : *start.left;
    }
    return start;
}

TreeNode findTreeNodeParent(const TreeNode &head, int val)
{
    TreeNode start = head;
    TreeNode *next = nullptr;
    int count{0};
    while ((start.left != nullptr || start.right != nullptr) && count < 15)
    {
        ++count;
        next = val > start.val ? start.right : start.left;
        if (next->val == val)
        {
            break;
        }
        start = *next;
    }
    return start;
}

bool testTreeNode(TreeNode &head)
{
    bool passed{false};
    TreeNode *start = &head;
    if (start == nullptr)
    {
        return true;
    }
    if (head.right != nullptr && head.right->val < head.val)
    {
        std::cout << "Failed Build Binary Tree " << head.right->val
                  << " is the right and should be greater than the head value: " << head.val << '\n';
        return false;
    }
    passed = testTreeNode(*head.right);

    if (head.left != nullptr && head.left->val > head.val)
    {
        std::cout << "Failed Build Binary Tree " << head.left->val
                  << " is the left and should be less than the head value: " << head.val << '\n';
        return false;
    }
    passed = testTreeNode(*head.left);

    if ((head.right && head.right->val == head.val) || (head.left && head.left->val == head.val))
    {
        std::cout << "Failed Build Binary Tree " << head.val << " is a duplicate entry" << '\n';
        return false;
    }
    return passed;
}

void testBuildBinaryTree(std::vector<int> vec)
{
    // std::vector<int> vec{ 56, 68, 34, 45, 74, 86, 62, 39, 21 };
    TreeNode node = buildBinaryTree(vec);
    bool passed = testTreeNode(node);
    if (passed)
    {
        std::cout << "Passed Build Binary Tree!" << '\n';
    }
}
