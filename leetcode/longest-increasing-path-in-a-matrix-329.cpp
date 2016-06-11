/*
 * =====================================================================================
 *
 *       Filename:  longest-increasing-path-in-a-matrix-329.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 20时47分37秒
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
    int longestIncreasingPath(vector<vector<int>>& matrix)
    {
        if (matrix.size() == 0)
            return 0;
        int size = matrix.size() * matrix[0].size();
        adjacency_list.resize(size);
        indegree.resize(size);
        for (int i = 0; i < (int)matrix.size(); ++i)
        {
            for (int j = 0; j < (int)matrix[i].size(); ++j)
            {
                int u = i * matrix[i].size() + j;
                if (i - 1 >= 0 && matrix[i][j] < matrix[i - 1][j])
                    adjacency_list[u].push_back((i - 1) * matrix[i].size() + j);
                if (i + 1 < (int)matrix.size() && matrix[i][j] < matrix[i + 1][j])
                    adjacency_list[u].push_back((i + 1) * matrix[i].size() + j);
                if (j - 1 >= 0 && matrix[i][j] < matrix[i][j - 1])
                    adjacency_list[u].push_back(i * matrix[i].size() + j - 1);
                if (j + 1 < (int)matrix[i].size() && matrix[i][j] < matrix[i][j + 1])
                    adjacency_list[u].push_back(i * matrix[i].size() + j + 1);
            }
        }
        for (auto line : adjacency_list)
            for (auto elem : line)
                ++indegree[elem];
        lenPath = 0;
        for (int i = 0; i < (int)indegree.size(); ++i)
            if (indegree[i] == 0) zeroPoint1.push(i);
        bfs();

        return lenPath;
    }

    void bfs()
    {
        while (!zeroPoint1.empty() || !zeroPoint2.empty())
        {
            if (!zeroPoint1.empty())
                ++lenPath;
            while (!zeroPoint1.empty())
            {
                int u = zeroPoint1.front();
                zeroPoint1.pop();
                for (auto v : adjacency_list[u])
                {
                    --indegree[v];
                    if (indegree[v] == 0) zeroPoint2.push(v);
                }
            }

            if (!zeroPoint2.empty())
                ++lenPath;
            while (!zeroPoint2.empty())
            {
                int u = zeroPoint2.front();
                zeroPoint2.pop();
                for (auto v : adjacency_list[u])
                {
                    --indegree[v];
                    if (indegree[v] == 0) zeroPoint1.push(v);
                }
            }
        }
    }

    int lenPath;
    queue<int> zeroPoint1;
    queue<int> zeroPoint2;
    vector<int> indegree;
    vector<vector<int>> adjacency_list;
};

int main(void)
{
    vector<vector<int>> m = {{9,9,4},{6,6,8},{2,1,1}};
    Solution sol;
    std::cout << sol.longestIncreasingPath(m) << std::endl;
    return 0;
}
