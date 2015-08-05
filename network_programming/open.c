/*
 * =====================================================================================
 *
 *       Filename:  open.c
 *
 *    Description:  about open operation
 *
 *        Version:  1.0
 *        Created:  2015年07月26日 20时23分29秒
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
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main ( int argc, char *argv[] )
{
    int fd;
    pid_t pid;
#ifdef _O_CLOEXEC
    fd = open(argv[1], O_CLOEXEC | O_WRONLY);
#else
    fd = open(argv[1], O_WRONLY);
#endif

    pid = fork();
    if (pid == 0)
    {
        if (execl("/bin/sleep", "sleep", "1000", NULL) < 0)
            perror("execl");
    }
    else
        write(fd, "abc", 3);
        sleep(1000);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
