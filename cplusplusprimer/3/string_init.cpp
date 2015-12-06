/*
 * =====================================================================================
 *
 *       Filename:  string_init.cpp
 *
 *    Description:  init string
 *
 *        Version:  1.0
 *        Created:  2015年12月03日 16时35分36秒 CST
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
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1;
    string s2 = s1;
    string s3 = "hiya";
    string s4(10, 'c'); // "cccccccccc"
    cout << s1 << "|" << s2 << "|" << s3 << "|" << s4 << endl;

    // 直接初始化和拷贝初始化
    string s5 = "hiya";     // 拷贝初始化 
    string s6("hiya");      // 直接初始化
    stirng s7(10, 'c');     // 直接初始化
    string s8 = string(10, 'c');    // 拷贝初始化 

}

