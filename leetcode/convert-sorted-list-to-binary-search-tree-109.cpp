/*
 * =====================================================================================
 *
 *       Filename:  convert-sorted-list-to-binary-search-tree-109.cpp
 *
 *    Description:  binary serach tree
 *
 *        Version:  1.0
 *        Created:  2016年06月09日 14时08分04秒
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

struct ListNode {
    /* data */
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) { }
};

void output(TreeNode* root)
{
    if (!root)
        return;
    output(root->left);
    std::cout << root->val << " ";
    output(root->right);
}

class Solution
{
public:
    TreeNode* sortedListToBST(ListNode* head)
    {
        int len = len_list(head);
        return buildTree(head, len);
    }

    TreeNode* buildTree(ListNode* head, int len)
    {
        if (len == 0)
            return NULL;

        ListNode* mid = advance(head, len / 2);
        TreeNode* root = new TreeNode(mid->val);
        root->left = buildTree(head, len / 2);
        root->right = buildTree(advance(mid, 1), len - len / 2 - 1);
        return root;
    }

    int len_list(ListNode* head)
    {
        int i = 0;
        for (; head; ++i, head = head->next)
            ;
        return i;
    }

    ListNode* advance(ListNode* head, int n)
    {
        for (; head && n; head = head->next, --n)
            ;
        return head;
    }
};

int main(void)
{
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    Solution sol;
    output(sol.sortedListToBST(head));
    return 0;
}
