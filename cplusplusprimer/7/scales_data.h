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
    // Scales_data() = default;    // default 表示使用合成构造函数
    Scales_data(const std::string &s, unsigned n, double p) :
                bookNo(s), units_sold(n), revenue(p*n) 
    {
        std::cout << "Scales_data(s, n, p)" << std::endl;
    }
    Scales_data() : Scales_data("", 0, 0)
    {
        std::cout << "Scales_data()" << std::endl;
    }
    Scales_data(const std::string &s) : Scales_data(s, 0, 0)
    {
        std::cout << "Scales_data(s)" << std::endl;
    }
    Scales_data(std::istream &is) : Scales_data()
    {
        std::cout << "Scales_data(is)" << std::endl;
        read(is, *this);
    }

    std::string isbn() const { return bookNo; }
    Scales_data& combine(const Scales_data&);

private:
    inline double avg_price() const;
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0;
};

inline double Scales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Scales_data add(const Scales_data&, const Scales_data&);
std::ostream &print(std::ostream&, const Scales_data&);
std::istream &read(std::istream&, Scales_data&);


#endif
