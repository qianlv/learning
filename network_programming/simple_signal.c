/*
 * =====================================================================================
 *
 *       Filename:  simple_signal.c
 *
 *    Description:  signal and pause usage 
 *
 *        Version:  1.0
 *        Created:  2015年07月24日 11时15分55秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv
 *   Organization:  
 *
 * =====================================================================================
 */


#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

static void sigint_handler(int signo)
{
    printf ("Caught SIGINT\n");
    exit (EXIT_SUCCESS);
}
int main ( int argc, char *argv[] )
{

    if (signal (SIGINT, sigint_handler) == SIG_ERR) {
        fprintf (stderr, "Cannot handle SINING\n");
        exit (EXIT_FAILURE);
    }
    
    for (;;)
        pause();

	return EXIT_SUCCESS;
}		/* ----------  end of function main  ---------- */


