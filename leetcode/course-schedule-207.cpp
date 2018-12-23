/*
 * =====================================================================================
 *
 *       Filename:  course-schedule-207.cpp
 *
 *    Description:  拓扑排序判断是否有环
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 18时02分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution
{
public:
    bool canFinish(int numCourses, vector<pair<int, int> >& prereqisites)
    {
        indegree.resize(numCourses);
        adjacency_list.resize(numCourses);
        for (auto elem : prereqisites)
        {
            ++indegree[elem.first];
            adjacency_list[elem.second].push_back(elem.first);
        }
        for (int i = 0; i < numCourses; ++i)
            if (indegree[i] == 0) zeroPoint.push(i);
        bfs();
        for (auto d : indegree)
            if (d > 0) return false;
        return true;
    }

    void bfs()
    {
        while (!zeroPoint.empty())
        {
            int u = zeroPoint.front();
            zeroPoint.pop();
            for (auto v : adjacency_list[u])
            {
                --indegree[v];
                if (indegree[v] == 0)
                    zeroPoint.push(v);
            }
        }
    }
    
    queue<int> zeroPoint;
    vector<int> indegree;
    vector<vector<int>> adjacency_list;
};

int main(void)
{

    return 0;
}
