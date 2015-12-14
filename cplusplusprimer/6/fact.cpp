/*
 * =====================================================================================
 *
 *       Filename:  fact.cpp
 *
 *    Description:    
 *
 *        Version:  1.0
 *        Created:  2015年12月09日 14时18分28秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "chapter6.h"

int fact(int val)
{
    int ret = 1;
    while (val > 1)
        ret *= val--;
    return ret;
}
