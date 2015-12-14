/*
 * =====================================================================================
 *
 *       Filename:  init_list.cpp
 *
 *    Description:  initializer_list
 *
 *        Version:  1.0
 *        Created:  2015年12月10日 10时04分29秒 CST
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

#include <sstream>
using std::ostringstream;

#include <string>
using std::string;

#include <initializer_list>
using std::initializer_list;

struct ErrCode
{
    ErrCode(int i): num(i) {}
    string msg()
    {
        ostringstream s;
        s << "Error Code " << num;
        return s.str();
    }
    int num;
};

void error_msg(initializer_list<string> li)
{
    for (auto beg = li.begin(); beg != li.end(); ++beg)
        cout << *beg << " ";
    cout << endl;
}

void error_msg(ErrCode e, initializer_list<string> li)
{
    cout << e.msg() << ": ";
    for (const auto &elem : li)
        cout << elem << " ";
    cout << endl;
}

int main()
{
    string expected = "description", actual = "some other case";
    
    if (expected != actual)
        error_msg({"functionX", expected, actual});
    else
        error_msg({"functionX", "okay"});

    if (expected != actual)
        error_msg(ErrCode(42), {"functionX", expected, actual});
    else
        error_msg(ErrCode(0), {"functionX", "okay"});
}
