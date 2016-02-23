/*
 * =====================================================================================
 *
 *       Filename:  basket.cpp
 *
 *    Description:  Class Basket
 *
 *        Version:  1.0
 *        Created:  2016年02月22日 10时25分23秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "basket.h"
#include <iostream>

double Basket::total_receipt(std::ostream &os) const
{
    double sum = 0.0;
    for (auto iter = items.cbegin();
              iter != items.cend();
              iter = items.upper_bound(*iter))
    {
        sum += print_total(os, **iter, items.count(*iter));
    }

    os << "Total Sale: " << sum << endl;
    return sum;
}
