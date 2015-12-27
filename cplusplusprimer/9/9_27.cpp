/*
 * =====================================================================================
 *
 *       Filename:  9_27.cpp
 *
 *    Description:  9.27
 *
 *        Version:  1.0
 *        Created:  2015年12月26日 14时23分30秒 CST
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

#include <forward_list>
using std::forward_list;

int main()
{
    forward_list<int> flist = {1, 2, 3, 10, 20, 7};
    auto prev = flist.before_begin();
    auto cur = flist.begin();
    for (; cur != flist.end(); )
    {
        if ((*cur) & 0x01)
            cur = flist.erase_after(prev);
        else
        {
            prev = cur;
            ++cur;
        }
    }
    for (auto &elem : flist)
    {
        cout << elem << endl;
    }
}
