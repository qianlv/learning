/*
 * =====================================================================================
 *
 *       Filename:  split-linked-list-in-parts-725.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月01日 14时52分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int linkLen = getLinkLen(root);
        int partLen = linkLen / k;
        int leftLen = linkLen % k;
        vector<ListNode*> res;
        for (int i = 0; i < k; i++) {
            int realPartLen = partLen + (leftLen > 0 ? 1:0);
            res.push_back(root);
            ListNode* pre = NULL;
            while(root && realPartLen > 0) {
                pre = root;
                root = root->next;
                realPartLen--;
            }
            if (pre) {
                pre->next = NULL;
            }
            leftLen--;
        }
        return res;
    }

    int getLinkLen(ListNode* root) {
        int num = 0;
        while(root) {
            num ++;
            root = root->next;
        }
        return num;
    }
};
