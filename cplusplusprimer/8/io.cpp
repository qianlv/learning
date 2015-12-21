/*
 * =====================================================================================
 *
 *       Filename:  io.cpp
 *
 *    Description:  IO
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 13时57分09秒 CST
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
using std::flush;
using std::ends;

#include <string>
using std::string;

int main()
{
    cout << "hi!" << endl;
    cout << "hi!" << flush;
    cout << "hi!" << ends;

    cout << std::unitbuf;
    cout << "hello world";
    cout << std::nounitbuf;
}
