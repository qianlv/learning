/*
 * =====================================================================================
 *
 *       Filename:  convert-sorted-array-to-binary-search-tree-108.cpp
 *
 *    Description:  binary search tree
 *
 *        Version:  1.0
 *        Created:  2016年06月09日 13时58分36秒
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
    TreeNode* sortedArrayToBST(vector<int>& nums)
    {
        return buildTree(nums, 0, nums.size() - 1);
    }

    TreeNode* buildTree(vector<int>& nums, int l, int r)
    {
        if (l > r)
            return NULL;
        int mid = l + (r - l) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = buildTree(nums, l, mid - 1);
        root->right = buildTree(nums, mid + 1, r);
        return root;
    }
};
