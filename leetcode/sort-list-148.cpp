/*
 * =====================================================================================
 *
 *       Filename:  sort-list-148.cpp
 *
 *    Description:  sort list O(n log n)
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 10时30分01秒
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
    ListNode* sortList(ListNode* head)
    {
        ListNode* carry = NULL;
        ListNode* counter[64] = {NULL};
        int fill = 0;
        while (head)
        {
            carry = head;
            head = head->next;
            carry->next = NULL;
            int i = 0;
            while (i < fill && counter[i])
            {
                carry = merge(carry, counter[i]);
                counter[i] = NULL;
                ++i;
            }
            counter[i] = carry;
            if (i == fill) ++fill;
        }
        for (int i = 1; i < fill; ++i)
            counter[i] = merge(counter[i-1], counter[i]);
        return counter[fill - 1];
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
    p = sol.sortList(head);
    print(p);
}

