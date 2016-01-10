/*
 * =====================================================================================
 *
 *       Filename:  12_23.cpp
 *
 *    Description:  12.23
 *
 *        Version:  1.0
 *        Created:  2016年01月07日 10时55分18秒 CST
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

#include <cstring>

#include <vector>
using std::vector;

char* link(const char *lh, const char *rh)
{
    size_t len = strlen(lh) + strlen(rh); 
    char *ret = new char[len + 1];
    ret[0] = '\0';
    strcat(ret, lh);
    strcat(ret, rh);
    return ret;
}

int main()
{
    char *link_str = link("hello", " world");
    cout << link_str << endl;
    delete [] link_str;
}
