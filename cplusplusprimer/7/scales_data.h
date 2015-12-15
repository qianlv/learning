/*
 * =====================================================================================
 *
 *       Filename:  scales_data.h
 *
 *    Description:  scales data
 *
 *        Version:  1.0
 *        Created:  2015年12月14日 14时35分07秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SCALES_DATA_H
#define SCALES_DATA_H

#include <string>
#include <iostream>

class Scales_data 
{
    friend Scales_data add(const Scales_data&, const Scales_data&);
    friend std::ostream &print(std::ostream&, const Scales_data&);
    friend std::istream &read(std::istream&, Scales_data&);

public:
    Scales_data() = default;    // default 表示使用合成构造函数
    Scales_data(const std::string &s) : bookNo(s) {}
    Scales_data(const std::string &s, unsigned n, double p) :
                bookNo(s), units_sold(n), revenue(p*n) {}
    Scales_data(std::istream &);

    std::string isbn() const { return bookNo; }
    Scales_data& combine(const Scales_data&);

private:
    double avg_price() const;
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0;
};

Scales_data add(const Scales_data&, const Scales_data&);
std::ostream &print(std::ostream&, const Scales_data&);
std::istream &read(std::istream&, Scales_data&);

#endif
