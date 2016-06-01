/*
 * =====================================================================================
 *
 *       Filename:  rotate-list-61.cpp
 *
 *    Description:  rotate list
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 19时29分34秒
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
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (head == NULL || head->next == NULL)
            return head;
        int len = len_list(head);
        if (k % len == 0)
            return head;
        
        k = len - k % len - 1;
        if (k == len - 1)
        {
            return flip(head);
        }

        ListNode* tail = advance(head, len - 1);
        ListNode* rotate_node = advance(head, k);
        tail->next = head;
        head = rotate_node->next;
        rotate_node->next = NULL;
        return head;

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

    ListNode* flip(ListNode* head)
    {
        if (!head)
        {
            return head;
        }

        ListNode* p1 = head;
        ListNode* p2 = head->next;
        while (p2)
        {
            ListNode* tmp = p2->next;
            p2->next = p1;
            p1 = p2;
            p2 = tmp;
        }
        head->next = NULL;
        return p1;
    }

};

int main()
{
    ListNode* head = new ListNode(1);
    ListNode* p = head;
    // const int a[] = {2, 2, 1};
    for (int i = 2; i < 3; ++i)
    {
        p->next = new ListNode(i);
        p = p->next;
    }
    Solution sol;
    p = sol.rotateRight(head, 2);
    print (p);
    cout << endl;
}
