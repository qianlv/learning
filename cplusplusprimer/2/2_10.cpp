/*
 * =====================================================================================
 *
 *       Filename:  2_10.cpp
 *
 *    Description:  init
 *
 *        Version:  1.0
 *        Created:  2015年11月22日 21时13分14秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>

std::string global_str;                         /* 空串 */
int global_int;                                 /* 0 */

int main()
{
    int local_int;                              /* 未定义, 编译器会警告 */
    std::string local_str;                      /* 空串 */
    std::cout << global_str << "---" << global_int << std::endl;
    std::cout << local_str << "+++" << local_int << std::endl;
}
