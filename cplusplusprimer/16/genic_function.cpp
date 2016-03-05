/*
 * =====================================================================================
 *
 *       Filename:  genic_function.cpp
 *
 *    Description:  genic_function
 *
 *        Version:  1.0
 *        Created:  2016年02月25日 14时32分05秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "genic_function.h"

namespace ch16
{

// template<typename T, typename F = less<T>>
// int compare(const T &v1, const T &v2, F f = F());
// 
// template <>
// int compare(const char* const &p1, const char* const &p2, int f)
// {
//     return std::strcmp(p1, p2);
// }

template <>
std::string debug_rep(const char *p)
{
    std::cout << " --" << std::endl;
    std::ostringstream ret;
    ret << "pointer: " << &p;
    if (p)
        ret << " " << p;
    else
        ret << " null pointer";
    return ret.str();
}

template <>
std::string debug_rep(char *p)
{
    std::cout << " --" << std::endl;
    std::ostringstream ret;
    ret << "pointer: " << &p;
    if (p)
        ret << " " << p;
    else
        ret << " null pointer";
    return ret.str();
}
}

