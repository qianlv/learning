/*
 * =====================================================================================
 *
 *       Filename:  9_18.cpp
 *
 *    Description:  9.18
 *
 *        Version:  1.0
 *        Created:  2015年12月24日 21时08分09秒 CST
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

#include <list>
using std::list;

#include <deque>
using std::deque;

int main()
{
    string word;
    deque<string> sde;
    while (cin >> word)
    {
        sde.push_back(word);
    }

    for (deque<string>::const_iterator iter = sde.begin();
            iter != sde.end(); ++iter)
    {
        cout << *iter << endl;
    }
}
