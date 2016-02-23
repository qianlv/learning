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
using std::cout;
using std::endl;

class Quote
{
public:
    Quote()
    {
        cout << "Quote: default constructor Quote\n";
    }

    Quote(const std::string &book, double sales_price):
        bookNo(book), price(sales_price)
    {
        cout << "Quote: constructor taking 2 parameters\n";
    }

    Quote(const Quote &q): bookNo(q.bookNo), price(q.price)
    {
        cout << "Quote: copy constructing\n";
    }

    Quote(Quote &&q) noexcept: bookNo(std::move(q.bookNo)), price(std::move(q.price)) 
    {
        cout << "Quote: move constructing\n";
    }

    Quote& operator= (const Quote &rhs)
    {
        if (this != &rhs)
        {
            bookNo = rhs.bookNo;
            price = rhs.price;
        }
        cout << "Quote: copy =() \n";
        return *this;
    }

    Quote& operator= (Quote &&rhs) noexcept
    {
        if (this != &rhs)
        {
            bookNo = std::move(rhs.bookNo);
            price = std::move(rhs.price);
        }
        cout <<"Quote: move =() \n";
        return *this;
    }

    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t) const;
    virtual ~Quote()
    {
        cout << "Quote: destructing Quote\n";
    }

    virtual Quote* clone() const & { return new Quote(*this);}
    virtual Quote* clone() && { return new Quote(std::move(*this));}

    void debug() const;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class DiscQuote : public Quote
{
public:
    DiscQuote()
    {
        cout << "DiscQuote: default constructor DiscQuote\n";
    }

    DiscQuote(const std::string &book, double sales_price, std::size_t qty, double disc):
        Quote(book, sales_price), quality(qty), discount(disc) 
    {
        cout << "DiscQuote: constructor taking 4 parameters\n";
    }

    DiscQuote(const DiscQuote &dq): Quote(dq), quality(dq.quality), discount(dq.discount)
    {
        cout << "DiscQuote: copy constructor.\n";
    }

    DiscQuote(DiscQuote &&dq) noexcept: Quote(std::move(dq)), 
        quality(std::move(dq.quality)), discount(std::move(dq.discount))
    {
        cout << "DiscQuote: move constructor.\n";
    }
    
    DiscQuote& operator= (const DiscQuote &dq)
    {
        if (this != &dq)
        {
            Quote::operator=(dq);
            quality = dq.quality;
            price = dq.price;
        }
        cout << "DiscQuote: copy =().\n";
        return *this;
    }

    DiscQuote& operator= (DiscQuote &&dq) noexcept
    {
        if (this != &dq)
        {
            Quote::operator=(std::move(dq));
            quality = std::move(dq.quality);
            price = std::move(dq.price);
        }
        cout << "DiscQuote: move =().\n";
        return *this;
    }

    virtual ~DiscQuote()
    {
        cout << "DiscQuote: destructing DiscQuote\n";
    }

    double net_price(std::size_t) const = 0;
protected:
    std::size_t quality = 0;
    double discount = 0.0;
};

class BulkQuote : public DiscQuote
{
public:
    BulkQuote()
    {
        cout << "BulkQuote: default constructing BulkQuote\n";
    }

    BulkQuote(const std::string &book, double sales_price, std::size_t qty, double disc):
        DiscQuote(book, sales_price, qty, disc) 
    {
        cout << "BulkQuote: constructor taking 4 parameters.\n";
    }
    
    BulkQuote(const BulkQuote &bq): DiscQuote(bq)
    {
        cout << "BulkQuote: copy constructor.\n";
    }

    BulkQuote(BulkQuote &&bq) noexcept: DiscQuote(std::move(bq))
    {
        cout << "BulkQuote: move constructor.\n";
    }

    BulkQuote& operator= (const BulkQuote &bq)
    {
        DiscQuote::operator=(bq);
        cout << "BulkQuote: copy =()\n";
        return *this;
    }

    BulkQuote& operator= (BulkQuote &&bq) noexcept
    {
        DiscQuote::operator=(std::move(bq));
        cout << "BulkQuote: move =()\n";
        return *this;
    }
    
    virtual ~BulkQuote()
    {
        cout << "BulkQuote: destructing BulkQuote\n";
    }

    BulkQuote* clone() const & { return new BulkQuote(*this); }
    BulkQuote* clone() && { return new BulkQuote(std::move(*this)); }
    double net_price(std::size_t) const override;
};

class LimitQuote : public DiscQuote
{
public:
    LimitQuote() = default;
    LimitQuote(const std::string &book, double sales_price, std::size_t max, double disc):
        DiscQuote(book, sales_price, max, disc) {}
    double net_price(std::size_t) const override;
};

double print_total(std::ostream &os, const Quote &item, size_t n);

#endif // BOOK_H_
