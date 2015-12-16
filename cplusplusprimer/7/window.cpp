/*
 * =====================================================================================
 *
 *       Filename:  window.cpp
 *
 *    Description:  Class Window
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 14时39分43秒 CST
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

#include "window.h"
#include "screen.h"

void Window_mgr::clear(ScreenIndex i)
{
    if (i >= screens.size()) return;
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

void Window_mgr::display() const
{
    for (auto &sc : screens)
    {
        sc.display(std::cout);
        std::cout << std::endl;
    }
}

Window_mgr::ScreenIndex 
Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

