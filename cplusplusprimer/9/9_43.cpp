/*
 * =====================================================================================
 *
 *       Filename:  9_43.cpp
 *
 *    Description:  9.43
 *                  This code doesn't compile on GCC. Please use Visual Studio 2015+ or Clang 3.6+ 
 *                  He He SB.
 *
 *        Version:  1.0
 *        Created:  2015年12月27日 15时13分42秒 CST
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

#include <vector>
using std::vector;

void replace(string &s, const string & oldVal, const string & newVal)
{
    for (auto iter = s.begin(); iter != s.end() - oldVal.size(); )
    {
        if (string(iter, iter + oldVal.size()) == oldVal)
        {
            iter = s.erase(iter, iter + oldVal.size());
            iter = s.insert(iter, newVal.begin(), newVal.end()); /* return void */
            iter += newVal.size();
        }
        else
        {
            ++iter;
        }
    }
}
int main()
{
    string s = "hello world!";
    replace(s, "l", "k");
    cout << s << endl;
}
