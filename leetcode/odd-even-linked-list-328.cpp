/*
 * =====================================================================================
 *
 *       Filename:  odd-even-linked-list-328.cpp
 *
 *    Description:  odd even linked list
 *
 *        Version:  1.0
 *        Created:  2016年05月31日 21时39分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
/*
 * Definition for singly-linked list.
 * struct listnode {
 *     int val;
 *     listnode *next;
 *     listnode(int x) : val(x), next(NULL) {}
 * };
 *
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
    ListNode* oddEvenList(ListNode* head)
    {
        ListNode* odd_head = new ListNode(0);
        ListNode* even_head = new ListNode(0);
        ListNode* odd = odd_head;
        ListNode* even = even_head;
        for (int j = 1; head; ++j, head = head->next)
        {
            if (j % 2 == 1)
            {
                odd->next = head;
                odd = head;
            }
            else
            {
                even->next = head;
                even = head;
            }
        }
        even->next = NULL;
        odd->next = NULL;
        odd->next = even_head->next;
        return odd_head->next;
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
    head = sol.oddEvenList(head);
    while (head)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}
