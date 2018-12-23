/*
 * =====================================================================================
 *
 *       Filename:  partition-list-86.cpp
 *
 *    Description:  partition
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 16时06分51秒
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
    ListNode* partition(ListNode* head, int x)
    {
        ListNode* less_head = new ListNode(0);
        ListNode* greater_head = new ListNode(0);
        ListNode* less_p = less_head;
        ListNode* greater_p = greater_head;
        while (head)
        {
            if (head->val < x)
            {
                less_p->next = head;
                less_p = less_p->next;
            }
            else
            {
                greater_p->next = head;
                greater_p = greater_p->next;
            }
            head = head->next;
        }
        greater_p->next = NULL;
        less_p->next = greater_head->next;
        return less_head->next;
    }
};

int main()
{
    ListNode* head = new ListNode(1);
    ListNode* p = head;
    int a[] = {1, 10, 3, 4, 8, 9, 1000};
    for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
    {
        p->next = new ListNode(a[i]);
        p = p->next;
    }
    Solution sol;
    print (head);
    cout << endl;
    p = sol.partition(head, 4);
    print(p);
}
