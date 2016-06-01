/*
 * =====================================================================================
 *
 *       Filename:  linked-list-cycle-II-142.cpp
 *
 *    Description:  判断链表是否又环返回环入口
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 14时30分54秒
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
    cout << endl;
}

class Solution
{
public:
    ListNode* detectCycle(ListNode* head)
    {
        if (!head || !head->next)
            return NULL;
        ListNode* step1 = head;
        ListNode* step2 = head;
        while (step2->next && step2->next->next)
        {
            step1 = step1->next;
            step2 = step2->next->next;
            if (step1 == step2)
            {
                step1 = head;
                while (step1 != step2)
                {
                    step1 = step1->next;
                    step2 = step2->next;
                }
                return step1;
            }
        }
        return NULL;
    }
};
