/*
 * =====================================================================================
 *
 *       Filename:  15_26.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月21日 22时10分31秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "book.h"

int main()
{
    BulkQuote bq1;
    BulkQuote bq2("ss", 2.05, 12, 0.3);
    bq2 = std::move(bq1);
}
