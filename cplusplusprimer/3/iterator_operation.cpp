/*
 * =====================================================================================
 *
 *       Filename:  iterator_operation.cpp
 *
 *    Description:  迭代器运算操作 
 *
 *        Version:  1.0
 *        Created:  2015年12月06日 21时22分13秒 CST
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

int main()
{
    vector <int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto beg = text.begin(), end = text.end();
    auto mid = text.begin() + (end - beg) / 2;
    int sought = 7;
    while (mid != end && *mid != sought)
    {
        if (sought < *mid)
            end = mid;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }

}
