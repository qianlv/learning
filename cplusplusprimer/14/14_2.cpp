/*
 * =====================================================================================
 *
 *       Filename:  14_2.cpp
 *
 *    Description:  14.2
 *
 *        Version:  1.0
 *        Created:  2016年02月17日 10时10分22秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "scales_data.h"

#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    Scales_data item, item2;
    cin >> item >> item2; 
    Scales_data item3 = item + item2;
    cout << item3 << endl;
    cout << (item + item2) << endl;
}
