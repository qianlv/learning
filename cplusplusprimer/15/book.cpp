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

inline double Quote::net_price(std::size_t n) const
{
    return n * price;
}

inline double BulkQuote::net_price(std::size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

inline double LimitQuote::net_price(std::size_t cnt) const
{
    if (cnt <= max_qty)
        return cnt * (1 - discount) * price;
    else
        return max_qty * (1 - discount) * price + (cnt - max_qty) * price;
}

double print_total(std::ostream &os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
