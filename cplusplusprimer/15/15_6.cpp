/*
 * =====================================================================================
 *
 *       Filename:  15_6.cpp
 *
 *    Description:  15.6
 *
 *        Version:  1.0
 *        Created:  2016年02月21日 11时00分26秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "book.h"
#include <iostream>
using std::cout;

int main()
{
    Quote qt("qt", 10.4);
    BulkQuote bqt("bqt", 10.4, 5, 0.3);
    print_total(cout, qt, 6);
    print_total(cout, bqt, 6);
}
