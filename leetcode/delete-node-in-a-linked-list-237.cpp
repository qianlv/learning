/*
 * =====================================================================================
 *
 *       Filename:  delete-node-in-a-linked-list.cpp
 *
 *    Description:  delete node in a linke list
 *
 *        Version:  1.0
 *        Created:  2016年05月31日 22时18分09秒
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
    void deleteNode(ListNode* node)
    {
        ListNode* next = node->next;
        std::swap(next->val, node->val);
        node->next = next->next;
    }
};
