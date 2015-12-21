/*
 * =====================================================================================
 *
 *       Filename:  account.c
 *
 *    Description:  Class Account
 *
 *        Version:  1.0
 *        Created:  2015年12月17日 21时20分04秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "account.h"

double Account::interestRate = initRate();
constexpr int Account::period;

void Account::rate(double newRate)
{
    interestRate = newRate;
}
