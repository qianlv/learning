/*
 * =====================================================================================
 *
 *       Filename:  reverse-linke-list-206.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年05月31日 22时53分41秒
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
    ListNode* reverseList(ListNode* head)
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
