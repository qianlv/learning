/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Main
 *
 *        Version:  1.0
 *        Created:  2016年02月22日 10时38分02秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "book.h"
#include "basket.h"

#include <iostream>
#include <memory>
#include <set>

int main()
{
    Basket basket;
    basket.add_item(std::make_shared<Quote>("123", 45));
    basket.add_item(std::make_shared<BulkQuote>("123", 45, 3, 0.15));
    Quote q1("234", 45);
    BulkQuote q2("234", 45, 3, 0.15);
    basket.add_item(q1);
    basket.add_item(q2);
    basket.add_item(Quote("345", 45));
    std::cout << basket.total_receipt(std::cout) << std::endl;
}
