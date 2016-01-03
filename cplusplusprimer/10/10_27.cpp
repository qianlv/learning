/*
 * =====================================================================================
 *
 *       Filename:  10_27.cpp
 *
 *    Description:  10.27
 *
 *        Version:  1.0
 *        Created:  2016年01月02日 21时50分28秒 CST
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

#include <algorithm>
#include <numeric>
#include <iterator>

int main()
{
    vector<int> ivec = {1, 2, 3, 1, 2, 3, 10, -1, -10, 10};
    list<int> li;
    sort(ivec.begin(), ivec.end());
    std::unique_copy(ivec.begin(), ivec.end(), std::back_inserter(li));
    for_each(li.begin(), li.end(), [] (int a) { cout << a << " "; });
    cout << endl;
}
