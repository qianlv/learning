/*
 * =====================================================================================
 *
 *       Filename:  3_22.cpp
 *
 *    Description:  3.22
 *
 *        Version:  1.0
 *        Created:  2015年12月06日 21时12分44秒 CST
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
    vector<string> text = {"one", "two", "three", "", "four"};
    typedef vector<string>::const_iterator const_iterator;
    typedef vector<string>::iterator iterator;
    for (iterator it = text.begin();
         it != text.end() && !it->empty(); ++it)
    {
        for (auto sit = it->begin(); sit != it->end(); ++sit)
            *sit = toupper(*sit);
        cout << *it << endl;
    }
}
