/*
 * =====================================================================================
 *
 *       Filename:  14_43.cpp
 *
 *    Description:  14.43
 *
 *        Version:  1.0
 *        Created:  2016年02月19日 14时00分34秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <string>
using std::placeholders::_1;

bool isdivided(int v, std::vector<int> iv)
{
    auto pred = std::bind(std::modulus<int>(), v, _1);
    return (std::all_of(iv.begin(), iv.end(), [&](int i) {return pred(i) == 0; }));
}

int main()
{
    auto data = { 2, 3, 4, 5 };
    int input;
    std::cin >> input;
    std::modulus<int> mod;
    auto predicator = [&](int i){ return 0 == mod(input, i); };
    auto is_divisible = std::all_of(data.begin(), data.end(), predicator);
    std::cout << (is_divisible ? "Yes!" : "No!") << std::endl;
    std::cout << (isdivided(input, data) ? "Yes!" : "No!") << std::endl;

    return 0;
}
