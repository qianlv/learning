/*
 * =====================================================================================
 *
 *       Filename:  daemon.c
 *
 *    Description:  Make a program become a daemon
 *
 *        Version:  1.0
 *        Created:  2015年07月13日 17时46分32秒 CST
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
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/fs.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    
    pid = fork();
    if ( pid == -1 ) {
        perror ("fork");
        return -1;
    } else if ( pid == 0) {
        exit (EXIT_SUCCESS);
    }
    
    /* create new session and process group */
    if ( setsid () == -1) {
        return -1;
    }

    /* set the working directory to the root directory */
    if ( chdir( "/" ) == -1 ) {
        return -1;
    }
    
    /* close all open files --NR_OPEN is overkill, but works */
    int i;
    for ( i = 0; i < NR_OPEN; ++i ) {
        close (i);
    }

    /* redirect fd's 0, 1, 2 to /dev/null */
    /* fd is sequence every open */
    open ("/dev/null", O_RDWR);
    dup (0);
    dup (0);
}


