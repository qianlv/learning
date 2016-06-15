/*
 * =====================================================================================
 *
 *       Filename:  unique-binary-search-trees-II-95.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 19时34分47秒
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
    vector<TreeNode*> generateTrees(int n)
    {
        if (n == 0) return {};
        return dfs(1, n);
    }

    vector<TreeNode*> dfs(int start, int end)
    {
        vector<TreeNode*> res;
        if (start > end)
        {
            res.push_back(NULL);
            return res;
        }
        
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> lefts = dfs(start, i - 1);
            vector<TreeNode*> rights = dfs(i + 1, end);
            for (auto l : lefts)
            {
                for (auto r : rights)
                {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
