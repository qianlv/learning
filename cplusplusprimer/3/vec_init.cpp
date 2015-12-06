/*
 * =====================================================================================
 *
 *       Filename:  vec_init.cpp
 *
 *    Description:  init vector
 *
 *        Version:  1.0
 *        Created:  2015年12月04日 16时46分02秒 CST
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
    vector<int> ivec(10, -1);
    vector<int> ivec2(ivec);
    vector<int> ivec3 = ivec;
    vector<string> articles = {"a", "an", "the"};
    vector<string> svec(10, "hi");
    vector<int>  ivec4(10);     // 10个元素, 初始化为默认值0;
    vector<string> svec1(10);   // 10个元素, 每个都是空string对象;
    vector<string> v7{10};
    vector<string> v8{10, "hi"};
    cout << v8[0] << endl;

}
