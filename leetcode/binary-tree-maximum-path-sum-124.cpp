/*
 * =====================================================================================
 *
 *       Filename:  binary-tree-maximum-path-sum-124.cpp
 *
 *    Description:  sum path
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 11时42分10秒
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
    int maxPathSum(TreeNode* root)
    {
        maxDepths[NULL] = INT32_MIN;
        secondMaxDepths[NULL] = INT32_MIN;
        ans = INT32_MIN;
        pathSum(root);
        return ans;
    }

    void pathSum(TreeNode* root)
    {
        if (!root)
            return;

        maxDepths[root] = INT32_MIN;
        secondMaxDepths[root] = INT32_MIN;
        if (root->left)
            pathSum(root->left);
        changeStates(root, root->left);
        if (root->right)
            pathSum(root->right);
        if (root->right)
            changeStates(root, root->right);
        //std::cout << maxDepths[root] << "|" << secondMaxDepths[root] << "root->val " << root->val << std::endl;
        int val = maxDepths[root] == INT32_MIN ? 0 : maxDepths[root];
        val += (secondMaxDepths[root] < 0 ? root->val : secondMaxDepths[root]);
        ans = std::max(ans, val - root->val);
    }

    void changeStates(TreeNode* cur, TreeNode* child)
    {
        int tmp = maxDepths[child] < 0 ? 0 : maxDepths[child];

        if (maxDepths[cur] < tmp + cur->val)
        {
            secondMaxDepths[cur] = maxDepths[cur];
            maxDepths[cur] = tmp + cur->val;
        }
        else
        {
            secondMaxDepths[cur] = std::max(secondMaxDepths[cur], tmp + cur->val);
        }
    }
    
    std::map<TreeNode*, int> maxDepths;
    std::map<TreeNode*, int> secondMaxDepths;
    int ans;
};

int main(void)
{
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(-1);
    //root->right = new TreeNode(3);
    Solution sol;
    std::cout << sol.maxPathSum(root) << std::endl;
    return 0;
}
