/*
 * =====================================================================================
 *
 *       Filename:  13_58.cpp
 *
 *    Description:  13.58
 *
 *        Version:  1.0
 *        Created:  2016年02月16日 14时34分20秒 CST
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

#include <algorithm>
#include <numeric>

class Foo
{
public:
    Foo sorted() && ;
    Foo sorted() const &;
private:
    vector<int> data;
};

Foo Foo::sorted() &&
{
    std::sort(data.begin(), data.end());
    cout << "Sorted() &&" << endl;
    return *this;
}

Foo Foo::sorted() const &
{
    // Normal way;
    // Foo ret(*this);
    // sort(ret.data.begin(), ret.data.end());
    // cout << "Sorted() const &" << endl;
    // return ret;

    // 13.57
    Foo ret(*this);
    return ret.sorted();
}

int main()
{
    Foo t;
    t.sorted();
}
