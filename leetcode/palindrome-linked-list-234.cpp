/*
 * =====================================================================================
 *
 *       Filename:  palindrome-linked-list-234.cpp
 *
 *    Description:  palindrome linked list
 *
 *        Version:  1.0
 *        Created:  2016年05月31日 22时33分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode (int x) : val(x), next(0) {}
};

class Solution
{
public:
    bool isPalindrome(ListNode* head)
    {
        int len = len_list(head);
        ListNode* head2 = advance(head, (len + 1) / 2);
        head2 = flip(head2);
        while (head2)
        {
            if (head->val != head2->val)
                return false;
            head = head->next;
            head2 = head2->next;
        }
        return true;
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
    const int a[] = {2, 2, 1};
    for (int i = 0; i < 3; ++i)
    {
        p->next = new ListNode(a[i]);
        p = p->next;
    }
    Solution sol;
    cout << sol.isPalindrome(head);
}
