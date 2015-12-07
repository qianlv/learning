/*
 * =====================================================================================
 *
 *       Filename:  3_32.cpp
 *
 *    Description:  3.32
 *
 *        Version:  1.0
 *        Created:  2015年12月07日 11时23分19秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

int main()
{
    const size_t size = 10;
    int arr[size];
    int carr[size];
    for (size_t i = 0; i < size; ++i)
        arr[i] = i;
    for (size_t i = 0; i < size; ++i)
        carr[i] = arr[i];

    for (size_t i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
    for (size_t i = 0; i < size; ++i)
        cout << carr[i] << " ";
    cout << endl;
}

