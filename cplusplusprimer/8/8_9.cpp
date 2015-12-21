/*
 * =====================================================================================
 *
 *       Filename:  8_9.cpp
 *
 *    Description:  8.9
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 19时32分31秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

istringstream& input(istringstream &is)
{
    string s;
    while (is >> s)
    {
        cout << s << endl;
    }
    is.clear();
    return is;
}

int main()
{
    istringstream is("1 2 3");
    input(is);
}

