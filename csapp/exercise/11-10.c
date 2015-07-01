// =====================================================================================
// 
//       Filename:  11-10.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2015年07月01日 17时01分32秒 CST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv@qq.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include "csapp.h"

int main(int argc, char *argv[])
{
    int n;
    rio_t rio;
    char buf[MAXBUF];
    int fd = STDIN_FILENO;
    if (argc == 2)
        fd = Open(argv[1], O_RDONLY, 0);
    Rio_readinitb(&rio, fd);
    while ((n = Rio_readnb(&rio, buf, MAXBUF)) != 0)
        Rio_writen(STDOUT_FILENO, buf, n);
    exit(0);

}
