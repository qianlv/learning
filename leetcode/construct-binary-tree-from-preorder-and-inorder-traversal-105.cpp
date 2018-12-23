/*
 * =====================================================================================
 *
 *       Filename:  construct-binary-tree-from-preorder-and-inorder-traversal-105.cpp
 *
 *    Description:  前序和中序 构造 二叉树 
 *
 *        Version:  1.0
 *        Created:  2016年06月08日 19时42分48秒
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

void output(TreeNode* root)
{
    if (!root)
        return;
    output(root->left);
    output(root->right);
    std::cout << root->val << " ";
}

class Solution
{
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        return build(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
    
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int l1, int r1, int l2, int r2)
    {
        if (l1 > r1)
            return NULL;
        TreeNode* root = new TreeNode(preorder[l1]);
        int i = l2;
        for (; i <= r2; ++i)
            if (preorder[l1] == inorder[i])
                break;
        root->left = build(preorder, inorder, l1 + 1, l1 + i - l2, l2, i - 1);
        root->right = build(preorder, inorder, l1 + i - l2 + 1, r1, i + 1, r2);
        return root;
    }
};

int main(void)
{
    Solution sol;
    vector<int> pre {2, 1, 3, 4, 5}, ino{1, 2, 4, 3, 5};
    output(sol.buildTree(pre, ino));
    return 0;
}
