/*
 * =====================================================================================
 *
 *       Filename:  validate-binary-search-tree-98.cpp
 *
 *    Description:  validate binary search tree
 *
 *        Version:  1.0
 *        Created:  2016年06月06日 10时53分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

class Solution
{
public:
    bool isValidBST(TreeNode* root)
    {
        initTree(root);
        return checkValidBST(root);
    } 

    bool checkValidBST(TreeNode* root)
    {
        if (!root)
            return true;
        if (check(root))
        {
            return checkValidBST(root->left) && checkValidBST(root->right);
        }
        return false;
    }

    bool check(TreeNode* root)
    {
        bool res = true;
        if (root->left)
            res = res && (root->val > max_node[root->left]);
        if (root->right)
            res = res && (root->val < min_node[root->right]);
        return res;
    }

    void initTree(TreeNode* root)
    {
        if (root)
        {
            max_node[root] = root->val;
            min_node[root] = root->val;
            if (root->left)
            {
                initTree(root->left);
                max_node[root] = std::max(max_node[root], max_node[root->left]);
                min_node[root] = std::min(min_node[root], min_node[root->left]);
            }
            if (root->right)
            {
                initTree(root->right);
                max_node[root] = std::max(max_node[root], max_node[root->right]);
                min_node[root] = std::min(min_node[root], min_node[root->right]);
            }
        }
    }

public:
    std::map<TreeNode*, int> max_node;
    std::map<TreeNode*, int> min_node;
};

int main(void)
{
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(20);
    Solution sol;
    std::cout << sol.isValidBST(root) << std::endl;
    return 0;
}
