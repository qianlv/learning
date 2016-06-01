/*
 * =====================================================================================
 *
 *       Filename:  remove-duplicates-from-sorted-list-83.cpp
 *
 *    Description:  remove duplicates from sorted list
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 16时30分15秒
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
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode* pre = head;
        ListNode* cur = head->next;
        while (cur)
        {
            if (pre->val == cur->val)
            {
                pre->next = cur->next;
            }
            else
            {
                pre = pre->next;
            }
            cur = cur->next;
        }
        return head;
    }
};
