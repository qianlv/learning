/*
 * =====================================================================================
 *
 *       Filename:  7_3.cpp
 *
 *    Description:  7.3
 *
 *        Version:  1.0
 *        Created:  2015年12月14日 19时12分23秒 CST
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
    if (cin >> total.bookNo >> total.units_sold >> total.revenue)
    {
        Scales_data trans;
        while (cin >> trans.bookNo >> trans.units_sold >> trans.revenue)
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                cout << total.bookNo << " " << total.units_sold 
                     << " " << total.revenue << endl;
                total = trans;
            }
        }
        cout << total.bookNo << " " << total.units_sold 
             << " " << total.revenue << endl;
    }
    else
    {
        std::cerr<< "No data?!" << std::endl;
        return -1;
    }

    return 0;
}

