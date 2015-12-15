/*
 * =====================================================================================
 *
 *       Filename:  7_13.cpp
 *
 *    Description:  7.13
 *
 *        Version:  1.0
 *        Created:  2015年12月15日 10时17分30秒 CST
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
    Scales_data total(cin);
    if (!total.isbn().empty())
    {
        std::istream &is = cin;
        while (is)
        {
            Scales_data trans(cin);
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
