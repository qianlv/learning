/*
 * =====================================================================================
 *
 *       Filename:  2_14.cpp
 *
 *    Description:  2.14
 *
 *        Version:  1.0
 *        Created:  2015年12月01日 15时09分20秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

int main()
{
    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
        sum += i;
    std::cout << i << " " << sum << std::endl;
}
