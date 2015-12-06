/*
 * =====================================================================================
 *
 *       Filename:  3_7.cpp
 *
 *    Description:  3.7
 *
 *        Version:  1.0
 *        Created:  2015年12月04日 16时01分58秒 CST
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

#include <cctype>
using std::ispunct;
using std::toupper;
using std::isspace;

int main()
{
    string s("hello world!!!");
    // nothing happen for s;
    for (char c : s)
        c = 'X';
    cout << s << endl;
}
