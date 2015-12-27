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
<<<<<<< HEAD

=======
>>>>>>> c1a049187d6c7e97936389e1c1c47f84ddbb59c4
#include "screen.h"
#include "window.h"
#include "scales_data.h"
#include "debug.h"

int main()
{
<<<<<<< HEAD
    Scales_data item;
    std::string null_book = "9-999-99999-9";
    item.combine(null_book);
    print(std::cout, item) << std::endl;
=======
    constexpr Debug io_sub(false, true, false);
    if (io_sub.any())
        std::cerr << "print appropriate error messages" << std::endl;
    constexpr Debug prob(false);
    if (prob.any())
        std::cerr << "print an error messages" << std::endl;

    // Scales_data total(std::cin);
    std::string null_book("abc");
    // Scales_data item = null_book;  // explicit Scales_data(std::string) cause error
    Scales_data item;
    item.combine(Scales_data(null_book));
    item.combine(static_cast<Scales_data>(std::cin));
>>>>>>> c1a049187d6c7e97936389e1c1c47f84ddbb59c4

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
