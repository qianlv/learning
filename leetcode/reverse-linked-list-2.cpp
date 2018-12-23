/*
 * =====================================================================================
 *
 *       Filename:  reverse-linked-list-2.cpp
 *
 *    Description:  reverse-linked-list-2
 *
 *        Version:  1.0
 *        Created:  2016年04月28日 21时08分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

/*
 * struct ListNode {
 *  int val;
 *  ListNode *next;
 *  ListNode(int x) : val(x), next(NULL) {}
 * }
 *
 * */

class Solution
{
public:
    ListNode* reverseBetween(ListNode* head, int m, int n)
    {
        ListNode* dumpy = new ListNode(0);
        dumpy->next = head;
        ListNode* p = dumpy;
        for (; --m; --n) p = p->next;
        ListNode* cur = p->next;
        ListNode* rtail = cur;
        ListNode* pre = NULL;
        while (n--)
        {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        rtail->next = cur; 
        p->next = pre;
        return dumpy->next;
    }
    
};
