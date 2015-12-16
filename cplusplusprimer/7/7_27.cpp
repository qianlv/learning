/*
 * =====================================================================================
 *
 *       Filename:  7_27.cpp
 *
 *    Description:  7.27
 *
 *        Version:  1.0
 *        Created:  2015年12月16日 11时15分52秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cout;
using std::endl;

#include "screen.h"

int main()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(0, 4).set('#').display(cout);
    cout << endl;
    myScreen.display(cout);
    cout << endl;
}
