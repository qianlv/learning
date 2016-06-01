/*
 * =====================================================================================
 *
 *       Filename:  remove-linked-list-elements-203.cpp
 *
 *    Description:  remove linked list elements
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 09时54分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <functional>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode (int x) : val(x), next(0) {}
};

void print(ListNode* head)
{
    while (head)
    {
        cout << head->val << " ";
        head = head->next;
    }
}

class Solution
{
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        ListNode* new_head = new ListNode(0);
        new_head->next = head;

        ListNode* pre = new_head;
        ListNode* cur = head;
        for (; cur; cur = cur->next)
        {
            if (cur->val == val)
            {
                pre->next = cur->next;
            }
            else
            {
                pre = cur;
            }
        }

        return new_head->next;
    }
};

int main()
{
    ListNode* head = new ListNode(1);
    ListNode* p = head;
    for (int i = 2; i < 7; ++i)
    {
        p->next = new ListNode(i);
        p = p->next;
    }
    Solution sol;
    p = sol.removeElements(head, 1);
    print(p);
}
