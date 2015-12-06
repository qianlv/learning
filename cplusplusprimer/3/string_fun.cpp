/*
 * =====================================================================================
 *
 *       Filename:  string_fun.cpp
 *
 *    Description:  string 内置函数
 *
 *        Version:  1.0
 *        Created:  2015年12月03日 17时30分42秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string line;
    while (getline(cin, line))
    {
        if (!line.empty())
            cout << line << endl;
        
        if (line.size() > 80)
            cout << line.size() << " " << line << endl;
    }
}
