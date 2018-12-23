/*
 * =====================================================================================
 *
 *       Filename:  remove-duplicates-from-sorted-list-II-82.cpp
 *
 *    Description:  remove duplicates from sorted list
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 16时46分50秒
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
        ListNode* new_head = new ListNode(0);
        new_head->next = head;
        
        ListNode* pre= new_head;
        ListNode* cur = new_head->next;
        int deleteVal = 0;
        while (cur)
        {
            if (cur->next != NULL && cur->next->val == cur->val)
            {
                deleteVal = cur->val;
                while (cur && cur->val == deleteVal)
                {
                    cur = cur->next;
                }
                pre->next = cur;
            }
            else
            {
                pre = cur;
                cur = cur->next;
            }
        }
        return new_head->next;
    }
};

int main()
{
    ListNode* head = new ListNode(1);
    ListNode* p = head;
    int a[] = {1, 1};
    for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
    {
        p->next = new ListNode(a[i]);
        p = p->next;
    }
    Solution sol;
    p = sol.deleteDuplicates(head);
    print(p);
}



