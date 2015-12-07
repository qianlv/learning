/*
 * =====================================================================================
 *
 *       Filename:  iterator.cpp
 *
 *    Description:  Iterator Usage
 *
 *        Version:  1.0
 *        Created:  2015年12月06日 20时56分34秒 CST
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
using std::isspace;

#include <vector>
using std::vector;

int main()
{
    string s("some string");
    if (s.begin() != s.end())
    {
        auto it = s.begin();
        *it = toupper(*it);
    }
    cout << s << endl;

    for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
        *it = toupper(*it);
    cout << s << endl;

    // 迭代器类型, begin, end, cbegin, cend;
    vector<int> v;
    vector<int>::iterator it1 = v.begin();
    vector<int>::const_iterator it3 = v.cbegin(); // v.cend();
    const vector<int> cv;
    vector<int>::const_iterator it2 = cv.begin();

    // -> 结合解引用和成员访问两个操作 
    vector<string> text = {"one", "two", "three", "", "four"};
    typedef vector<string>::const_iterator const_iterator;
    typedef vector<string>::iterator iterator;
    for (const_iterator it = text.begin();
         it != text.end() && !it->empty(); ++it)
        cout << *it << endl;

    vector<string>::difference_type diff = text.end() - text.begin();
    cout << diff << endl;
}
