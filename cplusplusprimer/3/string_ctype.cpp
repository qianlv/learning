/*
 * =====================================================================================
 *
 *       Filename:  string_ctype.cpp
 *
 *    Description:  string ctype
 *
 *        Version:  1.0
 *        Created:  2015年12月04日 15时38分10秒 CST
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
    string s("Hello World!!!");
    string::size_type punct_cnt = 0;
    for (auto c : s)
    {
        if (ispunct(c))
            ++punct_cnt;
    }
    cout << punct_cnt
         << " punctuation characters in " << s << endl;

    for (auto &c : s)
        c = toupper(c);
    cout << s << endl;

    string ss("some string");
    if (!ss.empty())
        ss[0] = toupper(ss[0]);
    cout << ss << endl;

    string ss1("some string");
    for (decltype(ss1.size()) index = 0;
         index != ss1.size() && !isspace(ss1[index]); ++index)
    {
        ss1[index] = toupper(ss1[index]);
    }
    cout << ss1 << endl;

    const string hexdigits = "0123456789ABCDEF";
    cout << "Enter a series of numbers between 0 and 15"
         << " separated by spaces. Hit ENTER when finished: "
         << endl;
    string result;
    string::size_type n;
    while (cin >> n)
    {
        if (n < hexdigits.size())
            result += hexdigits[n];
    }
    cout << "Your hex number is: " << result << endl;
}
