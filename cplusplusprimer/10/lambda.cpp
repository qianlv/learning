/*
 * =====================================================================================
 *
 *       Filename:  lambda.cpp
 *
 *    Description:  Lambda
 *
 *        Version:  1.0
 *        Created:  2016年01月01日 16时23分08秒 CST
 *       Revision:  none
 *       Compiler:  g++
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

#include "generic_algorithm.h"

void fcn1()
{
    size_t v1 = 42;
    auto f = [v1] { return v1; };
    v1 = 0;
    auto j = f();
    cout << v1 << " " << j << endl;
}

void fcn2()
{
    size_t v1 = 42;
    auto f = [&v1] { return ++v1; };
    v1 = 0;
    auto j = f();
    cout << v1 << " " << j << endl;
}

void fcn3()
{
    size_t v1 = 42;
    auto f = [v1] () mutable { return ++v1; };
    auto j = f();
    cout << v1 << " " << j << endl;
}

int main()
{
    vector<string> words = {"one", "two", "three", "four"};
    biggies(words, 4);
    fcn1();
    fcn2();
    fcn3();
    vector<int> vi = {1, -2, 3, -4, -6, 10};
    std::transform(vi.begin(), vi.end(), vi.begin(),
                   [] (int i) { return i < 0 ? -i : i; });
    // Error: return void
    // std::transform(vi.begin(), vi.end(), vi.begin(),
    //                [] (int i) 
    //                { if (i < 0) return -i; else return i;});
    std::transform(vi.begin(), vi.end(), vi.begin(),
                   [] (int i) -> int 
                   { if (i < 0) return -i; else return i;});
}
