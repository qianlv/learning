/*
 * =====================================================================================
 *
 *       Filename:  intersection-of-two-linked-lists-160.cpp
 *
 *    Description:  求两个链表交点
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 10时15分05秒
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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        if (!isIntersection(headA, headB))
            return NULL;
        int lenA = len_list(headA);
        int lenB = len_list(headB);
        if (lenA > lenB)
        {
            headA = advance(headA, lenA - lenB);
        }
        else
        {
            headB = advance(headB, lenB - lenA);
        }

        for (; headA != headB; headA = headA->next, headB = headB->next)
            ;
        return headA;
    }

    bool isIntersection(ListNode* headA, ListNode* headB)
    {
        if (!headA || !headB)
            return false;

        while (headA->next)
            headA = headA->next;
        while (headB->next)
            headB = headB->next;
        return headA == headB;
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

int main()
{
    ListNode* ite = new ListNode(1000);
    ListNode* headA = new ListNode(1);
    ListNode* p = headA;
    for (int i = 2; i < 1000; ++i)
    {
        p->next = new ListNode(i);
        p = p->next;
    }
    p->next = ite;

    ListNode* headB = new ListNode(1);
    p = headB;
    for (int i = 2; i < 7; ++i)
    {
        p->next = new ListNode(i);
        p = p->next;
    }
    p->next = ite;

    Solution sol;
    p = sol.getIntersectionNode(headA, headB); 
    print(p);
}
