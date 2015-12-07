/*
 * =====================================================================================
 *
 *       Filename:  3_17.cpp
 *
 *    Description:  3.17
 *
 *        Version:  1.0
 *        Created:  2015年12月06日 20时26分16秒 CST
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
using std::toupper;

#include <vector>
using std::vector;

int main()
{
    string word;
    vector<string> text;

    while (cin >> word)
    {
        text.push_back(word);
    }
    for (string &wd : text)
    {
        for (char &c : wd)
        {
            c = toupper(c);
        }
    }
    for (string wd : text)
        cout << wd << endl;
}
