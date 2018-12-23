/*
 * =====================================================================================
 *
 *       Filename:  swap-nodes-in-pairs.cpp
 *
 *    Description:  swap nodes in pairs
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 17时28分29秒
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
    ListNode* swapPairs(ListNode* head)
    {
    }

    ListNode* advance(ListNode* head, int n)
    {
        for (; head && n; head = head->next, --n)
            ;
        return head;
    }
};
