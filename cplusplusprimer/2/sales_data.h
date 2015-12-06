/*
 * =====================================================================================
 *
 *       Filename:  sales_data.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月03日 14时10分35秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct SalesData
{
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};
#endif
