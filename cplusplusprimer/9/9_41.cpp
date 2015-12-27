/*
 * =====================================================================================
 *
 *       Filename:  9_41.cpp
 *
 *    Description:  9.41 
 *
 *        Version:  1.0
 *        Created:  2015年12月27日 14时50分28秒 CST
 *       Revision:  none
 *       Compiler:  g++
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
    vector<char> cvec = {'h','e','l','l','o',' ','w','o','r','l','d','!'};
    string s(cvec.begin(), cvec.end());
    cout << s << endl;
}
