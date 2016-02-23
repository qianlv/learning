/*
 * =====================================================================================
 *
 *       Filename:  book.cpp
 *
 *    Description:  Class Quote, BulkQuote
 *
 *        Version:  1.0
 *        Created:  2016年02月20日 16时22分15秒 CST
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
using std::cin;
using std::endl;

inline double Quote::net_price(std::size_t n) const
{
    return n * price;
}

inline void Quote::debug() const
{
    cout << "data members of this class:\n"
         << "bookNo= " << bookNo
         << "price= " << price << endl;
}

inline double BulkQuote::net_price(std::size_t cnt) const
{
    if (cnt >= quality)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

inline double LimitQuote::net_price(std::size_t cnt) const
{
    if (cnt <= quality)
        return cnt * (1 - discount) * price;
    else
        return quality * (1 - discount) * price + (cnt - quality) * price;
}

double print_total(std::ostream &os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
