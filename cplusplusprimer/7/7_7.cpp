/*
 * =====================================================================================
 *
 *       Filename:  7_7.cpp
 *
 *    Description:  7.7
 *
 *        Version:  1.0
 *        Created:  2015年12月14日 19时40分33秒 CST
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
using std::cin;
using std::endl;

#include <string>

#include "scales_data.h"

int main()
{
    Scales_data total;
    if (read(cin, total))
    {
        Scales_data trans;
        while (read(cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {

                total.combine(trans);
            }
            else
            {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    }
    else
    {
        std::cerr<< "No data?!" << std::endl;
        return -1;
    }

    return 0;
}
