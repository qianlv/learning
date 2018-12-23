/*
 * =====================================================================================
 *
 *       Filename:  flatten-binary-tree-to-linked-list-114.cpp
 *
 *    Description:  flatten binary tree to linked list
 *
 *        Version:  1.0
 *        Created:  2016年06月10日 20时28分42秒
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

    std::cout << root->val << std::endl;
    output(root->left);
    output(root->right);
}

class Solution
{
public:
    void flatten(TreeNode* root)
    {
        flatten_core(root);
        //output(root);
    }

    TreeNode* flatten_core(TreeNode* root)
    {
        if (!root)
            return NULL;
        TreeNode* llast = NULL;
        TreeNode* rlast = NULL;
        if (root->left) 
            llast = flatten_core(root->left);
        if (root->right) 
            rlast = flatten_core(root->right);

        if (!root->left && !root->right)
        {
            return root;
        }
        else if (root->left && !root->right) 
        {
            TreeNode* tmp = root->left;
            root->right = tmp;
            root->left = NULL;
            if (rlast == NULL)
                rlast = llast;
            return rlast;
        }
        else if (!root->left && root->right)
        {
            return rlast;
        }
        else
        {
            llast->right = root->right;
            root->right = root->left;
            root->left = NULL;
            return rlast;
        }
    }
};

int main(void)
{
    TreeNode* tmp = NULL;
    TreeNode* root = new TreeNode(1);
    tmp = root;

    tmp->left = new TreeNode(2);
    tmp = tmp->left;

    tmp->left= new TreeNode(3);
    tmp->right = new TreeNode(4);
    tmp = tmp->left;

    tmp->left = new TreeNode(5);
    //output(root);
    Solution sol;
    sol.flatten(root);
    output(root);
    return 0;
}
