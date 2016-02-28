/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Main
 *
 *        Version:  1.0
 *        Created:  2016年02月23日 20时55分40秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "genic_function.h"
#include "vec.h"
#include "blob.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::list;

class A
{};

int main()
{
    // 16.4
    vector<int> ivec{1, 10, 11, 12};
    auto iter = ch16::find(ivec.begin(), ivec.end(), 10);
    cout << *iter << endl;
    list<string> lstr{"abe", "ed", "end"};
    auto liter = ch16::find(lstr.begin(), lstr.end(), "ed");
    cout << *liter << endl;

    //16.5
    const char carr[] = "hello";
    ch16::print(carr);

    // 16.6
    string sarr[] = {"abe", "ed", "end"};
    auto siter = ch16::find(ch16::begin(sarr), ch16::end(sarr), "ed");
    cout << *siter << endl;

    // 16.7
    cout << ch16::getsize(sarr) << endl;
    
    Blob<int> ia{1, 2, 3}, ia1{1, 2, 3}, ia2{2, 3, 4};
    cout << (ia == ia1) << " " << (ia == ia2) << endl;
    // vector<A> av{A()}, av1{A(),A()};
    // cout << (av == av1) << endl;
    
    // 16.16
    Vec<int> Ivec{1, 5, 4}, Ivec1{1, 3, 5, 1}, Ivec2(Ivec);
    for (auto iter = Ivec.begin(); iter != Ivec.end(); ++iter)
        cout << *iter << " ";
    cout << endl;
    cout << (Ivec < Ivec1) << " " << (Ivec == Ivec2) << endl;

    // 16.19
    ch16::output(Ivec, cout) << endl;
    // 16.29
    ch16::output2(Ivec, cout) << endl;
    
    Blob<string> a1(std::begin(sarr), std::end(sarr));
    Blob<int> a2(Ivec.begin(), Ivec.end());

    cout << std::max<double>(1, 1.2) << endl;
    
    int *p = new int(10);
    ch16::print1(cout, "ab", 1, p) << endl;
    ch16::errMsg(std::cerr, "ab", 1, 3.3) << endl;
    // ch16::print1(cout, "ab", Ivec, 1, "ve");
    
    auto str = ch16::make_shared<string>(10, 'c');
    cout << *str << endl;
}
