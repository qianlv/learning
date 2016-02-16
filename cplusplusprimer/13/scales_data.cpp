/*
 * =====================================================================================
 *
 *       Filename:  scales_data.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月14日 14时52分29秒 CST
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

#include "scales_data.h"

Scales_data::Scales_data(const Scales_data &orig):
    bookNo(orig.bookNo),
    units_sold(orig.units_sold),
    revenue(orig.revenue)
{
    cout << "Scales_data(const Scales_data &orig)" << endl;
}

Scales_data::~Scales_data()
{
    cout << "~Scales_data()" << endl;
}

Scales_data& Scales_data::combine(const Scales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue    += rhs.revenue;
    return *this;
}

Scales_data& Scales_data::operator= (const Scales_data &rhs)
{
    bookNo     = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue    = rhs.revenue;
    return *this;
}

std::istream &read(std::istream &is, Scales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Scales_data &item) 
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Scales_data add(const Scales_data &lhs, const Scales_data &rhs)
{
    Scales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}


