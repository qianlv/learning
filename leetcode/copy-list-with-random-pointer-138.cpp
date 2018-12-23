/*
 * =====================================================================================
 *
 *       Filename:  copy-list-with-random-pointer-138.cpp
 *
 *    Description:  deep copy
 *
 *        Version:  1.0
 *        Created:  2016年06月01日 15时36分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <map>
using namespace std;

struct RandomListNode
{
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x): label(x), next(NULL), random(NULL) {}
};

class Solution
{
public:
    RandomListNode* copyRandomList(RandomListNode* head)
    {
        std::map<RandomListNode*, RandomListNode*> old_new_node_map;
        RandomListNode* new_head = new RandomListNode(0);
        RandomListNode* p = head;
        RandomListNode* new_p = new_head;
        while (p)
        {
            new_p->next = new RandomListNode(p->label);
            new_p = new_p->next;
            old_new_node_map[p] = new_p;
            p = p->next;
        }

        new_p = new_head = new_head->next;
        p = head;
        while (p)
        {
            if (p->random != NULL)
            {
                new_p->random = old_new_node_map[p->random];
            }
            new_p = new_p->next;
            p = p->next;
        }
        return new_head;
    }
};
