/*
 * =====================================================================================
 *
 *       Filename:  str_example.c
 *
 *    Description:  about str function example
 *
 *        Version:  1.0
 *        Created:  2015年07月26日 14时03分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main ( int argc, char *argv[] )
{
    const char *st = "ab|/ab";
    printf("%s\n", strstr(st, "b|/"));
    char buf[20];
    scanf("%2[^ ]", buf);
    printf("%s\n", buf);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
