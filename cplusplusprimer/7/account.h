/*
 * =====================================================================================
 *
 *       Filename:  account.h
 *
 *    Description:  Class Account
 *
 *        Version:  1.0
 *        Created:  2015年12月17日 21时15分36秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>

class Account
{
public:
    void calculate()
    {
        amount += amount * interestRate;
    }
    static double rate()
    {
        return interestRate;
    }
    static void rate(double);
private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
    static constexpr int period = 30;
    double daily_tbl[period];
};
