/*
 * =====================================================================================
 *
 *       Filename:  find_char.cpp
 *
 *    Description:  find char
 *
 *        Version:  1.0
 *        Created:  2015年12月09日 15时10分29秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

string::size_type find_char(const string &s, char c,
                            string::size_type &occurs)
{
    auto ret = s.size();
    occurs = 0;
    for (decltype(ret) i = 0; i != s.size(); ++i)
    {
        if (s[i] == c)
        {
            if (ret == s.size())
            {
                ret = i;
            }
            ++occurs;
        }
    }
    return ret;
}

int main()
{
    string s;
    char c = 'a';
    while (cin >> s)
    {
        string::size_type occurs = 0;
        string::size_type pos = find_char(s, c, occurs);
        cout << pos << " " << occurs << endl;
    }
}
