/*
 * =====================================================================================
 *
 *       Filename:  house-robber-III-337.cpp
 *
 *    Description:  记忆搜索 DP
 *
 *        Version:  1.0
 *        Created:  2016年06月12日 15时51分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
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
    int rob(TreeNode* root)
    {
        if (!root)
            return 0;
        f1[NULL] = f2[NULL] = 0;
        dfs(root);
        return std::max(f1[root], f2[root]);
    }

    void dfs(TreeNode* root)
    {
        if (!root->left && !root->right)
        {
            f1[root] = root->val;
            f2[root] = 0;
        }

        if (root->left)
            dfs(root->left);
        if (root->right)
            dfs(root->right);
        f1[root] = root->val + f2[root->left] + f2[root->right];
        f2[root] = std::max(f1[root->left] + f1[root->right], f2[root]);
        f2[root] = std::max(f2[root->left] + f1[root->right], f2[root]);
        f2[root] = std::max(f1[root->left] + f2[root->right], f2[root]);
        f2[root] = std::max(f2[root->left] + f2[root->right], f2[root]);
    }

    std::unordered_map<TreeNode*, int> f1;
    std::unordered_map<TreeNode*, int> f2;
};

