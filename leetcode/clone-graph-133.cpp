/*
 * =====================================================================================
 *
 *       Filename:  clone-graph-133.cpp
 *
 *    Description:  clone graph
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 14时28分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

struct UndirectedGraphNode {
    int label;
    std::vector<UndirectedGraphNode*> neighbors;
    UndirectedGraphNode(int x) : label(x) { }
};

class Solution
{
public:
    UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node)
    {
        node_set.clear();
        if (!node)
            return NULL;
        UndirectedGraphNode* root = new UndirectedGraphNode(node->label);
        node_set[node] = root;
        travelGraph(node, root);
        return root;
    }

    void travelGraph(UndirectedGraphNode* node, UndirectedGraphNode* clone_node)
    {
        for (auto iter : node->neighbors)
        {
            if (node_set.find(&*iter) == node_set.end())
            {
                UndirectedGraphNode* child = new UndirectedGraphNode(iter->label);
                clone_node->neighbors.push_back(child);
                node_set[&*iter] = child;
                travelGraph(&*iter, child);
            }
            else
            {
                clone_node->neighbors.push_back(node_set[&*iter]);
            }
        }
    }

    std::unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> node_set;
};

int main(void)
{
    UndirectedGraphNode* root1 = new UndirectedGraphNode(1);
    UndirectedGraphNode* root2 = new UndirectedGraphNode(2);
    UndirectedGraphNode* root3 = new UndirectedGraphNode(3);
    root1->neighbors.push_back(root2);
    root1->neighbors.push_back(root3);
    root2->neighbors.push_back(root3);
    root3->neighbors.push_back(root3);
    Solution sol;
    auto res = sol.cloneGraph(root1);
    std::cout << res << std::endl;
    (void)res;
    return 0;
}
