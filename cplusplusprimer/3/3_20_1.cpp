/*
 * =====================================================================================
 *
 *       Filename:  3_20.cpp
 *
 *    Description:  3.20 
 *
 *        Version:  1.0
 *        Created:  2015年12月06日 20时32分29秒 CST
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
    int n;
    vector<int> ivec;
    while (cin >> n)
    {
        ivec.push_back(n);
    }

    if (ivec.empty())
    {
        cout << "input at least one integet" << endl;
        return -1;
    }
    if (ivec.size() == 1) 
    {
        cout << "only one integet " << ivec[0] << endl;
        return 0;
    }

    for (vector<int>::size_type i = 0; i != ivec.size() -1; ++i)
        cout << ivec[i] + ivec[i+1] << " ";
    cout << endl;
}
