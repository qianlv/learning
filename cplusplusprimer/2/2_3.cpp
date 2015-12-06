/*
 * =====================================================================================
 *
 *       Filename:  2_3.cpp
 *
 *    Description:  unsiged
 *
 *        Version:  1.0
 *        Created:  2015年11月15日 15时48分52秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

int main ( int argc, char *argv[] )
{
    unsigned u1 = 10, u2 = 42;
    std::cout << u2 - u1 << std::endl;
    std::cout << u1 - u2 << std::endl;

    int i1 = 10, i2 = 42;
    std::cout << i2 - i1 << std::endl;
    std::cout << i1 - i2 << std::endl;
    std::cout << i1 - u1 << std::endl;
    std::cout << u1 - i1 << std::endl;
}
