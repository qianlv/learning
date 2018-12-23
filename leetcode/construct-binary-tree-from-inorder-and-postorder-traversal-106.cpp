/*
 * =====================================================================================
 *
 *       Filename:  construct-binary-tree-from-inorder-and-postorder-traversal-106.cpp
 *
 *    Description:  中序和后序 构造 二叉树
 *
 *        Version:  1.0
 *        Created:  2016年06月08日 20时14分12秒
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
    std::cout << root->val << " ";
    output(root->left);
    output(root->right);
}

class Solution
{
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
    {
        return build(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
    }

    TreeNode* build(vector<int>& inorder, vector<int>& postorder, int l1, int r1, int l2, int r2)
    {
        if (l1 > r1)
            return NULL;
        TreeNode* root = new TreeNode(postorder[r1]);
        int i = l2;
        for (; i <= r2; ++i)
            if (postorder[r1] == inorder[i])
                break;
        int len = i - l2;
        root->left = build(inorder, postorder, l1, l1 + len - 1,  l2, i - 1);
        root->right = build(inorder, postorder, l1 + len, r1 - 1, i + 1, r2);
        return root;
    }
};

int main(void)
{
    Solution sol;
    vector<int> pre {1, 4, 5, 3, 2}, ino{1, 2, 4, 3, 5};
    output(sol.buildTree(ino, pre));
    return 0;
}
