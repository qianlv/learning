/*
 * =====================================================================================
 *
 *       Filename:  8_1.cpp
 *
 *    Description:  8.1
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 13时30分41秒 CST
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
using std::istream;

#include <string>
using std::string;

istream& input(istream &is)
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
    istream &is = input(cin);    
    cout << bool(is.rdstate() & is.badbit) << " "
         << bool(is.rdstate() & is.failbit) << " "
         << bool(is.rdstate() & is.eofbit) << " "
         << bool(is.rdstate() & is.goodbit) << endl;
}
