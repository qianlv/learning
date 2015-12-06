/*
 * =====================================================================================
 *
 *       Filename:  string_deal.cpp
 *
 *    Description:  two string 
 *
 *        Version:  1.0
 *        Created:  2015年12月03日 17时51分36秒 CST
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
    string str = "Hello";
    string phrase = "Hello World";
    string slang = "Hiya";
    cout <<  (str < phrase) << " " << (slang >str) << endl;

    string s1 = "hello, ", s2 = "world\n";
    string s3 = s1 + s2;
    s1 += s2;
    cout << s3 << s1;

    string s4 = s1 + " " + s2;
    cout << s4;

    string s;
    while (getline(cin, s, 'a'))
        cout << s << endl;
}

