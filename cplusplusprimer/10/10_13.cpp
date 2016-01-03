/*
 * =====================================================================================
 *
 *       Filename:  10_13.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月29日 16时26分22秒 CST
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

#include <algorithm>
#include <numeric>

bool get_length(const string &s)
{
    return s.size() >= 5;
}

int main()
{
    vector<string> svec = {"abceffe", "ae", "12", "1", "onetowfjdk"};
    auto pivot = std::partition(svec.begin(), svec.end(), get_length);
    for (auto iter = svec.begin(); iter != pivot; ++iter)
        cout << *iter << " ";
    cout << endl;
}
