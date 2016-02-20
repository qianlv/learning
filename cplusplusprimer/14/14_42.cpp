/*
 * =====================================================================================
 *
 *       Filename:  14_42.cpp
 *
 *    Description:  14.42
 *
 *        Version:  1.0
 *        Created:  2016年02月19日 11时52分16秒 CST
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

int main()
{
    std::vector<int> ivec {1, 11, 111, 1111};
    int count = std::count_if(ivec.begin(), ivec.end(),
                std::bind(std::greater<int>(), _1, 1024));
    std::cout << "count=" << count << std::endl;
    std::vector<std::string> svec {"pooh", "pooh", "three"};
    auto iter = std::find_if(svec.cbegin(), svec.cend(),
                std::bind(std::not_equal_to<std::string>(), _1, "pooh"));
    std::cout << *iter << std::endl;
    std::transform(ivec.begin(), ivec.end(), ivec.begin(), std::bind(std::multiplies<int>(), _1, 2));
    for (auto iter : ivec)
        std::cout << iter << std::endl;
}
