/*
 * =====================================================================================
 *
 *       Filename:  populating-next-right-pointers-in-each-node-II-117.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月10日 22时21分35秒
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
        for (TreeLinkNode* parent = NULL; root;)
        {
            //std::cout << "root = " << root->val << std::endl;
            TreeLinkNode* tmp = root;
            for (; tmp; tmp = tmp->next)
            {
                if (!parent) tmp->next = NULL;
                else if (parent->left == tmp)
                {
                    if (parent->right)
                        tmp->next = parent->right;
                    else
                    {
                        parent = parent->next;
                        while (parent)
                        {
                            if (parent->left || parent->right)
                            {
                                tmp->next = parent->left ? parent->left : parent->right;
                                break;
                            }
                            parent = parent->next;
                        }
                    }
                }
                else if (parent->right == tmp)
                {
                    parent = parent->next;
                    while (parent)
                    {
                        if (parent->left || parent->right)
                        {
                            tmp->next = parent->left ? parent->left : parent->right;
                            break;
                        }
                        parent = parent->next;
                    }
                }
            }

            while (root)
            {
                if (root->left || root->right)
                    break;
                root = root->next;
            }
            parent = root;
            if (root)
                root = root->left ? root->left : root->right;
        }
    }

};

int main(void)
{
    TreeLinkNode* root = new TreeLinkNode(1);
    //TreeLinkNode* tmp = root;
    //tmp->left = new TreeLinkNode(2);
    //tmp->right = new TreeLinkNode(3);
    //tmp->right->right = new TreeLinkNode(6);
    //tmp->right->right->right = new TreeLinkNode(8);
    //tmp = tmp->left;
    //tmp->left = new TreeLinkNode(4);
    //tmp->right = new TreeLinkNode(5);
    //tmp->left->left = new TreeLinkNode(7);

    Solution sol;
    sol.connect(root);
    return 0;
}
