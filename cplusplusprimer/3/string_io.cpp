/*
 * =====================================================================================
 *
 *       Filename:  string_io.cpp
 *
 *    Description:  string io 
 *
 *        Version:  1.0
 *        Created:  2015年12月03日 16时42分46秒 CST
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
    // string s;
    // cin >> s;
    // cout << s << endl;

    // string s1, s2;
    // cin >> s1 >> s2;
    // cout << s1 << s2 << endl;

    // string word;
    // while (cin >> word)
    //     cout << word << endl;
    
    string line;
    while (getline(cin, line))
        cout << line << endl;
    return 0;
}
