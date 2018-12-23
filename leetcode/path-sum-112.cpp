/*
 * =====================================================================================
 *
 *       Filename:  path-sum-112.cpp
 *
 *    Description:  path sum
 *
 *        Version:  1.0
 *        Created:  2016年06月10日 19时37分21秒
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
    bool hasPathSum(TreeNode* root, int sum)
    {
        if (!root)
            return false;
        pathSum(root, sum);
        return res;
    }

    void pathSum(TreeNode* root, int sum)
    {
        if (res)
        {
            return;
        }
        if (!root->left && !root->right)
        {
            sum -= root->val;
            res = (sum == 0);
        }
        if (root->left) pathSum(root->left, sum - root->val);
        if (root->right) pathSum(root->right, sum - root->val);
    }

    bool res = false;
};

