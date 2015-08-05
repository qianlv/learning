/*
 * =====================================================================================
 *
 *       Filename:  another_simple_signal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年07月24日 11时27分54秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

extern const char * const sys_siglist[];

static void signal_handler (int signo)
{
    if (signo == SIGINT)
        printf ("Caught %s\n", sys_siglist[signo]);
    else if (signo == SIGTERM)
        printf ("Caught %s\n", sys_siglist[signo]);
    else {
        fprintf (stderr, "Unexpected signal\n");
        exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
}

int main ( int argc, char *argv[] )
{
    if (signal (SIGINT, signal_handler) == SIG_ERR) {
        fprintf (stderr, "Cannot handle SIGINT!\n");
        exit (EXIT_FAILURE);
    }

    if (signal (SIGTERM, signal_handler) == SIG_ERR) {
        fprintf (stderr, "Cannot handle SIGTERM!\n");
        exit (EXIT_FAILURE);
    }

    if (signal (SIGPROF, SIG_DFL) == SIG_ERR) {
        fprintf (stderr, "Cannot handle SIGPROF!\n");
        exit (EXIT_FAILURE);
    }

    if (signal (SIGHUP, SIG_IGN) == SIG_ERR) {
        fprintf (stderr, "Cannot ignore SIGHUNP!\n");
        exit (EXIT_FAILURE);
    }

    for (;;)
        pause();

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


