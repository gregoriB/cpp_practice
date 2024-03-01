#pragma once
#include <iostream>
#include <vector>

class TreeNode
{
  public:
    TreeNode *left;
    TreeNode *right;
    int val;

    TreeNode(int value);
};

TreeNode buildBinaryTree(std::vector<int> vec);
TreeNode insertIntoTree(TreeNode &head, int val);
TreeNode findTreeNode(const TreeNode &head, int val);
TreeNode findTreeNodeParent(const TreeNode &head, int val);

void testBuildBinaryTree(std::vector<int> vec);
