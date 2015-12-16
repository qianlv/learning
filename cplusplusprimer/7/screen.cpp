/*
 * =====================================================================================
 *
 *       Filename:  screen.cpp
 *
 *    Description:  Class Screen
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 10时08分46秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>

#include "screen.h"

char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}

void Screen::some_member() const
{
    ++access_str;
}

Screen::pos Screen::size() const
{
    return height * width;
}

