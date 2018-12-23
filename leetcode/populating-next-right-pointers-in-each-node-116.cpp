/*
 * =====================================================================================
 *
 *       Filename:  populating-next-right-pointers-in-each-node-116.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月10日 22时10分57秒
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

struct TreeLinkNode {
    int val;
    TreeLinkNode* left;
    TreeLinkNode* right;
    TreeLinkNode* next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) { }
};

void output(TreeLinkNode* root)
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
    void connect(TreeLinkNode* root)
    {
        if (!root)
            return;
        connectDFS(root, NULL);
    }
    
    void connectDFS(TreeLinkNode* root, TreeLinkNode* parent)
    {
        if (!parent) root->next = NULL;
        else if (parent->left == root)
            root->next = parent->right;
        else if (parent->right == root)
        {
            root->next = parent->next ? parent->next->left : NULL;
        }
        if (root->left)
            connectDFS(root->left, root);
        if (root->right)
            connectDFS(root->right, root);
    }
};
