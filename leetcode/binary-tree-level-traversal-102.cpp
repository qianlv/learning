#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > allRes;
        if (root==NULL) {
            return allRes;
        }
        queue<TreeNode*> que[2];
        int cur(0);
        que[cur].push(root);
        while (true) {
            vector<int> res;
            while (!que[cur].empty()) {
                TreeNode* t = que[cur].front();
                que[cur].pop();
                res.push_back(t->val);
                if (t->left != NULL) {
                    que[1-cur].push(t->left);
                }
                if (t->right != NULL) {
                    que[1-cur].push(t->right);
                }
            }
            cur = 1 - cur;
            allRes.push_back(res);
            if (que[cur].empty()) {
                break;
            }
        }
        return allRes;
    }
};
