/*
 * =====================================================================================
 *
 *       Filename:  recover-binary-serach-tree-99.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月07日 09时43分29秒
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
    void recoverTree(TreeNode* root)
    {
        swap1 = NULL; swap2 = NULL;
        pre = NULL;
        findSwapNode(root);
        //std::cout << swap1->val << "|" << swap2->val << std::endl;
        std::swap(swap1->val, swap2->val);
    }

    void findSwapNode(TreeNode* root)
    {
        if (!root)
            return;

        findSwapNode(root->left);
        //if (pre)
            //std::cout << "pre val:" << pre->val << std::endl;
        if (pre && root && pre->val > root->val)
        {
            if (NULL == swap1)
            {
                swap1 = pre; swap2 = root;
            }
            else
            {
                swap2 = root;
            }
        }
        pre = root;
        //std::cout << root->val << std::endl;
        findSwapNode(root->right);
    }

    TreeNode* pre;
    TreeNode* swap1, *swap2;
};

int main(void)
{
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(3);
    root->right = new TreeNode(1);
    Solution sol;
    sol.recoverTree(root);
    return 0;
}
