/*
 * =====================================================================================
 *
 *       Filename:  9_22.cpp
 *
 *    Description:  9.22
 *
 *        Version:  1.0
 *        Created:  2015年12月24日 21时29分36秒 CST
 *       Revision:  none
 *       Compiler:  gcc
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

void double_and_insert(std::vector<int>& v, int some_val)
{
    auto mid = [&]{ return v.begin() + v.size() / 2; };
    for (auto curr = v.begin(); curr != mid(); ++curr)
        if (*curr == some_val)
            ++(curr = v.insert(curr, 2 * some_val));
}


int main()
{
    vector<int> ivec = {1, 2, 1, 1, 9, 1, 3, 10, 3};
    vector<int> ivec2 = {1, 2, 1, 1, 9, 1, 3, 10, 3};
    
    for (auto iter = ivec.begin(); iter != ivec.begin() + ivec.size() / 2; ++iter)
    {
        if (*iter == 1)
        {
            iter = ivec.insert(iter, 2);
            ++iter;
        }
    }
    for (auto &elem : ivec)
        cout << elem << " ";
    cout << endl;
    double_and_insert(ivec2, 1);
    for (auto &elem : ivec2)
        cout << elem << " ";
    cout << endl;
    
}
