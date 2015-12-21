/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  main
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 11时07分01秒 CST
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
#include "window.h"
#include "scales_data.h"

int main()
{
    Scales_data item;
    std::string null_book = "9-999-99999-9";
    item.combine(null_book);
    print(std::cout, item) << std::endl;

    Screen myScreen(5, 3, '$');
    const Screen blank(5, 3, '0');
    myScreen.move(1, 3).set('#').display(std::cout);
    blank.display(std::cout);
    std::cout << std::endl;
    Window_mgr my_windows({myScreen, blank});
    my_windows.display();
    my_windows.clear(0);
    my_windows.display();

    Screen::pos ht(24), wd(80);
    Screen scr(ht, wd, ' ');
    Screen *p = &scr;
    char c = scr.get();
    c = p->get();
    std::cout << c << std::endl;
}
