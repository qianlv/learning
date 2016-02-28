/*
 * =====================================================================================
 *
 *       Filename:  find.h
 *
 *    Description:  genic find
 *
 *        Version:  1.0
 *        Created:  2016年02月23日 14时42分50秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iterator>
using std::InputIterator;

template<InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T& val)
{
    while (first != last)
    {
        if (*first == val) return first;
        ++first;
    }
    return last;
}
