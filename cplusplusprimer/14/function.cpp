/*
 * =====================================================================================
 *
 *       Filename:  function.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月19日 14时43分27秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
using std::cout;
using std::cin;
using std::endl;
using std::function;
using std::map;
using std::string;

int add(int i, int j) { return i + j; }
auto mod = [] (int i, int j) { return i % j; };
struct divide
{
    int operator() (int denominator, int divisor)
    {
        return denominator / divisor;
    }
};

int main()
{
    function<int(int, int)> f1 = add;
    function<int(int, int)> f2 = divide();
    function<int(int, int)> f3 = [] (int i, int j) { return i * j; };
    cout << f1(4, 2) << endl;
    cout << f2(4, 2) << endl;
    cout << f3(4, 2) << endl;
    map<string, function<int(int, int)>> binops = {
        {"+", add},
        {"-", std::minus<int>()},
        {"/", divide()},
        {"*", [] (int i, int j) { return i * j; }},
        {"%", mod}
    };
    cout << binops["+"](10, 5) << endl;
    cout << binops["-"](10, 5) << endl;
    cout << binops["/"](10, 5) << endl;
    cout << binops["*"](10, 5) << endl;
    cout << binops["%"](10, 5) << endl;
}
