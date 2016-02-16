/*
 * =====================================================================================
 *
 *       Filename:  13_8.cpp
 *
 *    Description:  13.8
 *
 *        Version:  1.0
 *        Created:  2016年01月10日 15时15分19秒 CST
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

#include "hasptr.h"

int main()
{
    HasPtr hp("hello world");
    HasPtr hp_operator;
    hp_operator = hp;
}
