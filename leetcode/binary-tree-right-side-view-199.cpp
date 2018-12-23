/*
 * =====================================================================================
 *
 *       Filename:  binary-tree-right-side-view-199.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 15时30分21秒
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
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

template <typename T>
void output(const std::vector<T>& vec)
{
    std::for_each(vec.begin(), vec.end(),
                [](const T& v) {
                    cout << v << " ";
                });
    cout << endl;
}

class Solution
{
public:
    vector<int> rightSideView(TreeNode* root)
    {
        vector<int> res;
        if (!root)
            return res;
        que1.push(root);
        while (!que1.empty() || !que2.empty())
        {
            TreeNode* cur = NULL;
            while (!que1.empty())
            {
                cur = que1.front();
                que1.pop();
                if (cur->left)
                    que2.push(cur->left);
                if (cur->right)
                    que2.push(cur->right);
            }
            if (cur) res.push_back(cur->val);

            cur = NULL;
            while (!que2.empty())
            {
                cur = que2.front();
                que2.pop();
                if (cur->left)
                    que1.push(cur->left);
                if (cur->right)
                    que1.push(cur->right);
            }
            if (cur) res.push_back(cur->val);
        }
        return res;
    }

    std::queue<TreeNode*> que1;
    std::queue<TreeNode*> que2;
};

int main(void)
{
    TreeNode* root = new TreeNode(1); 
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    Solution sol;
    output(sol.rightSideView(root));
    return 0;
}
