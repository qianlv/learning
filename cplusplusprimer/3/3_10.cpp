/*
 * =====================================================================================
 *
 *       Filename:  3_10.cpp
 *
 *    Description:  3.10
 *
 *        Version:  1.0
 *        Created:  2015年12月04日 16时24分08秒 CST
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
    string str;
    while (getline(cin, str))
    {
        for (char c : str)
        {
            if (!ispunct(c))
                cout << c;
        }
    }
    cout << endl;
}
