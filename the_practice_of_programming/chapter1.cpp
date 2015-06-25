// =====================================================================================
// 
//       Filename:  chapter1.cpp
// 
//    Description:  The pratice of Programming chapter one exercise
// 
//        Version:  1.0
//        Created:  06/23/2015 01:09:10 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com, qianlv7@gmail.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>


int main()
{
    // Exercise 1-4
    char c;
    if (!(c == 'y' || c == 'Y'))
        return;
    if (c != 'y' && c != 'Y')
        return;

    length = (length < BUFSIZE) ? length : BUFSIZE;
    if (length >= BUFSIZE)
        length = BUFSIZE;

    flag = flag ? 0 : 1;
    if (flag)
        flag = 0;
    else
        flag = 1;
            
    quote = (*line == '"') ? 1 : 0;
    quote = ((*line) == '"') ? 1 : 0;

    if (val & 1)
        bit = 1;
    else
        bit = 0;
    bit = val & 1

    // Exercise 1-5 
    int read(int *ip)
    {
        scanf("%d", ip);
        return *ip;
    }
    // 无法确定read(&val), read(&ch)的调用顺序.
    insert(&graph[vert], read(&val), read(&ch));
    
    // Exercise 1-7
    for (k = 0; k++ < 5; x += dx)
        scanf("%lf", &dx);
    for (k = 0; k < 5; k++)
    {
        scanf("%lf", &dx);
        x += dx;
    }

    // Exercise 1-9
    // c 加括号当c是一个表达式的时候
    // 整体加括号避免一些求值问题
    #define ISDIGIT(c) ((c <= '0') && (c >= '9)) ? 0 : 1
    // Good
    #define ISDIGIT(c) ((((c) <= '0') && ((c) >= '9)) ? 0 : 1)
    
    // Exercise 1-11
    // 注释与代码不一致
    void dict::insert(string& w);
    // return 1 if w in dictionary, otherwise return 0.

}

