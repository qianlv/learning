/*
 * =====================================================================================
 *
 *       Filename:  seq_container.cpp
 *
 *    Description:  Sequential Containers 
 *
 *        Version:  1.0
 *        Created:  2015年12月26日 14时30分40秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <deque>
using std::deque;

#include <forward_list>
using std::forward_list;

#include <queue>
using std::queue;

void print_size_capacity(vector<int> &ivec)
{
    cout << " ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    return;
}

int main()
{
    list<int> ilist(10, 42);
    ilist.resize(15);
    ilist.resize(25, -1);
    for (auto &elem : ilist)
        cout << elem << " ";
    cout << endl;

    ilist.resize(5);
    for (auto &elem : ilist)
        cout << elem << " ";
    cout << endl;

    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = vi.begin();
    while (iter != vi.end())
    {
        if (*iter % 2)
        {
            iter = vi.insert(iter, *iter);
            iter += 2;
        }
        else
        {
            iter = vi.erase(iter);
        }
    }
    for (auto &elem : vi)
        cout << elem << " ";
    cout << endl;

    vector<int> ivec;
    print_size_capacity(ivec);
    for (vector<int>::size_type ix = 0; ix != 24; ++ix)
        ivec.push_back(ix);
    print_size_capacity(ivec);
    ivec.reserve(50);
    print_size_capacity(ivec);
    ivec.shrink_to_fit();
    print_size_capacity(ivec);

    queue<string, list<string>> lque;
    queue<string, vector<string>> vque;
    queue<string, deque<string>> dque;
    lque.push("abc");
    cout << lque.front() << endl;
}
