/*
 * =====================================================================================
 *
 *       Filename:  linked-list-cycle-141.cpp
 *
 *    Description:  判断链表是否又环
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 14时39分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

B
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
    bool hasCycle(ListNode* head)
    {
        ListNode* step1 = head;
        ListNode* step2 = head;
        do
        {
            if (!step1 || !step2)
                return false;
            step1 = step1->next;
            step2 = step2->next;
            if (!step2)
                return false;
            step2 = step2->next;
            if (step1 == step2)
                return true;
        } while (true)
    }
};

