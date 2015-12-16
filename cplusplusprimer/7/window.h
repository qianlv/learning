/*
 * =====================================================================================
 *
 *       Filename:  window.h
 *
 *    Description:  Class Window_mgr
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 10时24分03秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <vector>

class Screen;

class Window_mgr
{

public:
    Window_mgr() = default;
    Window_mgr(std::vector<Screen> sc) : screens(sc) {}
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
    void display() const;
    ScreenIndex addScreen(const Screen&);
private:
    std::vector<Screen> screens;
};

#endif
