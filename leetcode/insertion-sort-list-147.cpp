/*
 * =====================================================================================
 *
 *       Filename:  insertion-sort-list-147.cpp
 *
 *    Description:  插入排序
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 21时18分58秒
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
    ListNode* insertionSortList(ListNode* head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode* carry = NULL;
        while (head)
        {
            ListNode *tmp = head;
            head = head->next;
            tmp->next = NULL;
            carry = merge(tmp, carry);
        }
        return carry;
    }

    ListNode* merge(ListNode* head1, ListNode* head2)
    {
        ListNode* new_head = new ListNode(0);
        ListNode* p = new_head;
        while (head1 && head2)
        {
            if (head1->val < head2->val)
            {
                p->next = head1;
                head1 = head1->next;
            }
            else
            {
                p->next = head2;
                head2 = head2->next;
            }
            p = p->next;
        }
        if (head1)
            p->next = head1;
        if (head2)
            p->next = head2;
        return new_head->next;
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
    p = sol.insertionSortList(head);
    print (p);
}
