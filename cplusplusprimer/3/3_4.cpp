/*
 * =====================================================================================
 *
 *       Filename:  3_4.cpp
 *
 *    Description:  3.4
 *
 *        Version:  1.0
 *        Created:  2015年12月04日 15时11分47秒 CST
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
    string str1, str2;
    while (cin >> str1 >> str2)
    {
        if (str1 == str2)
            cout << "Two string is equal!" << endl;
        else
            cout << ((str1 > str2) ? str1 : str2) << endl;
    }
    return 0;
}

