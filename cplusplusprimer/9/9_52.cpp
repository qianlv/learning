/*
 * =====================================================================================
 *
 *       Filename:  9_52.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月27日 19时59分41秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stack>
#include <string>
#include <iostream>

using std::string; using std::cout; using std::endl; using std::stack;

int main()
{
    string expression{ "(This) is (pezy)." };
    bool bSeen = false;
    stack<char> stk;
    string::size_type lpos;
    for (string::size_type pos = 0; pos != expression.size(); )
    {
        string::value_type s = expression[pos];
        if (s == '(') 
        {
            bSeen = true;
            lpos = pos;
            ++pos;
            continue;
        }
        else if (s == ')') 
        {
            bSeen = false;
            string repstr;
            while (!stk.empty())
            {
                repstr += stk.top();
                stk.pop();
            }
            expression.replace(lpos + 1, repstr.size(), repstr);
        }

        ++pos;
        if (bSeen) stk.push(s);
    }
    
    cout << expression << endl;
    
    return 0;
}
