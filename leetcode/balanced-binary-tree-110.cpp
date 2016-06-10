/*
 * =====================================================================================
 *
 *       Filename:  balanced-binary-tree-110.cpp
 *
 *    Description:  判断是否为平衡二叉树
 *
 *        Version:  1.0
 *        Created:  2016年06月10日 18时40分39秒
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
#include <cstdlib>
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
    bool isBalanced(TreeNode* root)
    {
        calculateTreeDepth(root);
        return res;
    }

    int calculateTreeDepth(TreeNode* root)
    {
        if (!root)
        {
            return 0;
        }
        int ldepth = calculateTreeDepth(root->left);
        int rdepth = calculateTreeDepth(root->right);
        if (std::abs(rdepth - ldepth) > 1)
            res = false;
        return std::max(ldepth, rdepth) + 1;
    }
    
    bool res = true;
};
