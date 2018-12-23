/*
 * =====================================================================================
 *
 *       Filename:  sum-root-to-leaf-numbers-129.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 14时07分00秒
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
#include <climits>
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
    int sumNumbers(TreeNode* root)
    {
        res = 0;
        sumPath(root, 0);
        return res;
    }

    void sumPath(TreeNode* root, int sum)
    {
        if (!root)
        {
            return;
        }
        if (!root->left && !root->right)
        {
            res += 10 * sum + root->val;
            return;
        }

        if (root->left)
            sumPath(root->left, sum * 10 + root->val);
        if (root->right)
            sumPath(root->right, sum * 10 + root->val);

    }

    int res;
};
