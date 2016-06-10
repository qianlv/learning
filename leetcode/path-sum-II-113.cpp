/*
 * =====================================================================================
 *
 *       Filename:  path-sum-II-113.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月10日 19时53分11秒
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
#include <vector>
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
    vector<vector<int>> pathSum(TreeNode* root, int sum)
    {
        vector<int> path;    
        calPath(path, root, sum);
        return res;
    }
    
    void calPath(vector<int>& path, TreeNode* root, int sum)
    {
        if (!root)
            return;
        path.push_back(root->val);
        if (!root->left && !root->right)
        {
            sum -= root->val;
            if (sum == 0)
                res.push_back(path);
        }
        if (root->left) calPath(path, root->left, sum - root->val);
        if (root->right) calPath(path, root->right, sum - root->val);
        path.pop_back();
    }

    vector<vector<int>> res;
};
