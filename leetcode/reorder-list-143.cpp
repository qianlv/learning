/*
 * =====================================================================================
 *
 *       Filename:  reorder-list-143.cpp
 *
 *    Description:  reorder list
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 11时09分48秒
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
    void reorderList(ListNode* head)
    {
        int len = len_list(head);
        if (len <= 2)
            return;

        ListNode* insert_list = advance(head, len - len / 2);
        ListNode* tail = advance(head, len - len / 2 - 1);
        tail->next = NULL;
        insert_list = reverseList(insert_list);

        ListNode* p1 = head;
        ListNode* p2 = head->next;
        while (insert_list)
        { 
            p1->next = insert_list;
            ListNode* tmp = insert_list->next;
            insert_list->next = p2;
            insert_list = tmp;
            p1 = p2;
            if (!p2)
                break;
            p2 = p2->next;
        }
        // print (head);
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

int main()
{
    cout << "--" << endl;
    ListNode* head = new ListNode(1);
    ListNode* p = head;
    for (int i = 2; i <= 4; ++i)
    {
        p->next = new ListNode(i);
        p = p->next;
    }
    cout << "--" << endl;
    Solution sol;
    sol.reorderList(head);
}
