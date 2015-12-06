/*
 * =====================================================================================
 *
 *       Filename:  3_5.cpp
 *
 *    Description:  3.5
 *
 *        Version:  1.0
 *        Created:  2015年12月04日 15时14分51秒 CST
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
    string str;
    for (string buffer; cin >> buffer; str += (str.empty() ? "" : " ") + buffer)
        ;
    cout << str << endl;
}
