/*
 * =====================================================================================
 *
 *       Filename:  14_35.cpp
 *
 *    Description:  14.35
 *
 *        Version:  1.0
 *        Created:  2016年02月19日 11时08分35秒 CST
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
#include <vector>
using std::istream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class InputString
{
public:
    InputString(istream &i = cin): is(i) {}
    string operator() () const 
    {
        string str;
        std::getline(is, str);
        return is ? str : string();
    }
private:
    istream &is;
};

int main()
{
    InputString is;
    cout << is() << endl;
    vector<string> sv;
    for (string tmp; !(tmp = is()).empty(); )
        sv.push_back(tmp);
    for (const auto &str : sv)
        cout << str << endl;
}
