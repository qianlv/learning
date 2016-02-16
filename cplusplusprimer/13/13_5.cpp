/*
 * =====================================================================================
 *
 *       Filename:  13_5.cpp
 *
 *    Description:  13.5
 *
 *        Version:  1.0
 *        Created:  2016年01月10日 14时07分48秒 CST
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

#include "hasptr.h"

int main()
{
    
    HasPtr hp("hello world");
    HasPtr hp_copy = hp;
}
