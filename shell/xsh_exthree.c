/*
 * @file     xsh_exthree.c
 * @provides xsh_exthree
/ *
 * $Id: xsh_exthree.c 1337 2013-09-25 11:11:11Z mkeele $
 */
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#include <stddef.h> //is this needed?
#include <stdio.h> //is this needed?
#include <exthree.h>

/**
 * Shell command (extwo).
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_exthree(int nargs, char *args[])
{
    /* Output help, if '--help' argument was supplied */
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
    {
        printf("Usage: %s\n\n", args[0]);
        printf("Description:\n");
        printf("\tCreates two threads and print characters(shares code)\n");
        printf("Options:\n");
        printf("\t--help\tdisplay this help and exit\n");
        return OK;
    }

    /* Check for correct number of arguments */
    if (nargs > 1)
    {
        fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
    }
    if (nargs < 1)
    {
        fprintf(stderr, "%s: too few arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
    }

    exthree();

    return OK;
}
