/*
 * =====================================================================================
 *
 *       Filename:  basket.h
 *
 *    Description:  Class Basket
 *
 *        Version:  1.0
 *        Created:  2016年02月22日 10时14分29秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BASKET_H_
#define BASKET_H_

#include "book.h"

#include <memory>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

class Basket
{
public:
    void add_item(const std::shared_ptr<Quote> &sale)
    {
        items.insert(sale);
    }
    
    void add_item(const Quote &sale)
    {
        std::cout << "add_item &" << std::endl;
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }

    void add_item(Quote &&sale)
    {
        std::cout << "add_item &&" << std::endl;
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    double total_receipt(std::ostream&) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

#endif // BASKET_H_
