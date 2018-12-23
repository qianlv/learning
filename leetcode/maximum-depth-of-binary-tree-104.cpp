/*
 * =====================================================================================
 *
 *       Filename:  maximum-depth-of-binary-tree-104.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月08日 16时43分35秒
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
    int maxDepth(TreeNode* root)
    {
        if (!root)
            return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
