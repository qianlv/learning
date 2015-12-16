/*
 * =====================================================================================
 *
 *       Filename:  screen.h
 *
 *    Description:  Class Screen
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 09时53分35秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <string>

#include "window.h"

class Screen
{
    friend void Window_mgr::clear(ScreenIndex);
    // friend class Window_mgr;
public:
    typedef std::string::size_type pos;
    // using pos = std::string::size_type;
    Screen() = default;
    Screen(pos ht, pos wd) :
        height(ht), width(wd), contents(ht * wd, ' ') { }    
    Screen(pos ht, pos wd, char c) : 
        height(ht), width(wd), contents(ht * wd, c) { }

    char get() const
    {
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const;

    Screen &set(char);
    Screen &set(pos, pos, char);

    Screen &move(pos r, pos c);

    Screen &display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }

    const Screen &display(std::ostream &os) const
    {
        do_display(os);
        return *this;
    }

    pos size() const;
    
    void some_member() const;


private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_str;

private:
    void do_display(std::ostream &os) const
    {
        os << contents;
    }
};

inline Screen& Screen::move(pos r, pos c)
{
    cursor = r * width + c;
    return *this;
}

inline Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}

#endif
