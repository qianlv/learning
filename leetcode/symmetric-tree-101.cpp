/*
 * =====================================================================================
 *
 *       Filename:  symmetric-tree-101.cpp
 *
 *    Description:  mirror of binary tree
 *
 *        Version:  1.0
 *        Created:  2016年06月08日 15时39分21秒
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

template <typename T>
void output(const std::vector<T>& vec)
{
    std::for_each(vec.begin(), vec.end(),
                [](const T& v) {
                    cout << v << " ";
                });
    cout << endl;
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

class Solution
{
public:
    bool isSymmetric(TreeNode* root)
    {
        if (!root)
            return true;
        return isDFS(root->left, root->right);
    }

    bool isDFS(TreeNode* left, TreeNode* right)
    {
        if (!left && !right)
            return true;
        if (!left || !right)
            return false;
        if (left->val != right->val)
            return false;
        return isDFS(left->left, right->right) && isDFS(left->right, right->left);
    }

};

int main(void)
{
    TreeNode* root = new TreeNode(1); 
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    Solution sol;
    std::cout << sol.isSymmetric(root) << std::endl;
    return 0;
}
