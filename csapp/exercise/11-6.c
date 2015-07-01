// =====================================================================================
// 
//       Filename:  11-6.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2015年07月01日 16时41分34秒 CST
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
    int fd1, fd2;
    fd1 = Open("foo.txt", O_RDONLY, 0);
    printf("fd1 = %d\n", fd1);
    fd2 = Open("bar.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);
    Close(fd2);
    fd2 = Open("baz.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);
    exit(0);
}
