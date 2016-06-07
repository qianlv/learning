/*
 * =====================================================================================
 *
 *       Filename:  same-tree-100.cpp
 *
 *    Description:  same tree
 *
 *        Version:  1.0
 *        Created:  2016年06月07日 15时46分23秒
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

class Solution
{
public:
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if (p == NULL && q == NULL)
        {
            return true;
        }
        else if (p && q)
        {
            return p->val == q->val && 
                   isSameTree(p->left, q->left) &&
                   isSameTree(p->right, q->right);
        }
        return false;
    }
};
int main(void)
{
    return 0;
}
