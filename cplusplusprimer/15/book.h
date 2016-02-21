/*
 * =====================================================================================
 *
 *       Filename:  book.h
 *
 *    Description:  Book 
 *
 *        Version:  1.0
 *        Created:  2016年02月20日 14时09分40秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BOOK_H_
#define BOOK_H_

#include <iostream>
#include <string>
#include <algorithm>

class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price):
        bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t) const;
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class BulkQuote : public Quote
{
public:
    BulkQuote() = default;
    BulkQuote(const std::string &book, double sales_price, std::size_t qty, double disc):
        Quote(book, sales_price), min_qty(qty), discount(disc) {}
    double net_price(std::size_t) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

class LimitQuote : public Quote
{
public:
    LimitQuote() = default;
    LimitQuote(const std::string &book, double sales_price, std::size_t max, double disc):
        Quote(book, sales_price), max_qty(max), discount(disc) {}
    double net_price(std::size_t) const override;
private:
    std::size_T max_qty = 0;
    double discount = 0.0;
};

double print_total(std::ostream &os, const Quote &item, size_t n);

#endif // BOOK_H_
