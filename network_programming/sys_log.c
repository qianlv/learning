/*
 * =====================================================================================
 *
 *       Filename:  sys_log.c
 *
 *    Description:  syslog usage
 *
 *        Version:  1.0
 *        Created:  2015年07月25日 15时53分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[])
{ 
    char *op;
    op = argv[0];
    op = strrchr(op, '/');
    openlog(op, LOG_NDELAY | LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "%s",op);
    return 0;
}
