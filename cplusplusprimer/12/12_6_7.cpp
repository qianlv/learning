/*
 * =====================================================================================
 *
 *       Filename:  12_6_7.cpp
 *
 *    Description:  12.6 12.7 
 *
 *        Version:  1.0
 *        Created:  2016年01月06日 10时07分16秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::string;

using Vptr = vector<int>*;

Vptr make_dynamicall()
{
    return new vector<int> {};
}

Vptr input(Vptr vec)
{
    int tmp;
    while (cin >> tmp)
    {
        vec->push_back(tmp);
    }
    return vec;
}

void print(Vptr vec)
{
    for (const auto &elem : *vec)
        cout << elem << " ";
    cout << endl;
}

using Sptr = shared_ptr<vector<int>>;

Sptr make_with_shared_ptr()
{
    return make_shared<vector<int>>();
}

Sptr input(Sptr vec)
{
    int tmp;
    while (cin >> tmp)
    {
        vec->push_back(tmp);
    }
    return vec;
}

void print(Sptr vec)
{
    for (const auto &elem : *vec)
        cout << elem << " ";
    cout << endl;
}


int main()
{
    auto vec = input(make_dynamicall());
    print(vec);
    delete vec;
    auto svec = input(make_with_shared_ptr());
    print(svec);
}
