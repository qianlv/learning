// =====================================================================================
// 
//       Filename:  11-7.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2015年07月01日 16时50分31秒 CST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv@qq.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include "csapp.h"

int main()
{
    int n;
    rio_t rio;
    char buf[MAXBUF];
    
    Rio_readinitb(&rio, STDIN_FILENO);
    while ((n = Rio_readnb(&rio, buf, MAXBUF)) != 0)
        Rio_writen(STDOUT_FILENO, buf, n);
    exit(0);

}
