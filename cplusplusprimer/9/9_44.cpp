/*
 * =====================================================================================
 *
 *       Filename:  9_44.cpp
 *
 *    Description:  9.44 
 *
 *        Version:  1.0
 *        Created:  2015年12月27日 16时23分04秒 CST
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

void replace(string &s, const string &oldVal, const string &newVal)
{
    size_t size = s.size() >= oldVal.size() ? s.size() - oldVal.size() : s.size(); /* size() 无符号数, 防止溢出 */
    for (string::size_type pos = 0; pos <= size; )
    {
        if (s.substr(pos, oldVal.size()) == oldVal)
        {
            s.replace(pos, oldVal.size(), newVal);
            pos += newVal.size();
        }
        else
        {
            ++pos;
        }
    }
}
int main()
{
    string s = "";
    replace(s, "l", "lllll");
    cout << s << endl;
}
