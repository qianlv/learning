/*
 * =====================================================================================
 *
 *       Filename:  minimum-depth-of-binary-tree-111.cpp
 *
 *    Description:  min depth of binary tree 
 *
 *        Version:  1.0
 *        Created:  2016年06月10日 19时07分22秒
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
    int minDepth(TreeNode* root)
    {
        if (!root)
            return 0;
        if ((!root->left && root->right) || (root->left && !root->right))
        {
            return std::max(minDepth(root->left), minDepth(root->right)) + 1;
        }
        return std::min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};
