/*
 * =====================================================================================
 *
 *       Filename:  9_47.cpp
 *
 *    Description:  9.47
 *
 *        Version:  1.0
 *        Created:  2015年12月27日 18时44分22秒 CST
 *       Revision:  none
 *       Compiler:  g++
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

int main()
{
    string str("ab2c3d7R4E6");
    string number("0123456789");
    string alphabet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    string::size_type pos = 0;
    while ((pos = str.find_first_of(number, pos)) != string::npos)
    {
        cout << str[pos] << " ";
        ++pos;
    }
    cout << endl;
    
    pos = 0;
    while ((pos = str.find_first_of(alphabet, pos)) != string::npos)
    {
        cout << str[pos] << " ";
        ++pos;
    }
    cout << endl;

    pos = 0;
    while ((pos = str.find_first_not_of(alphabet, pos)) != string::npos)
    {
        cout << str[pos] << " ";
        ++pos;
    }
    cout << endl;

    pos = 0;
    while ((pos = str.find_first_not_of(number, pos)) != string::npos)
    {
        cout << str[pos] << " ";
        ++pos;
    }
    cout << endl;
}
