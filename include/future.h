/*
 * @file future.h
 *
 * $Id: future.h 1337 2013-09-25 11:11:11Z mkeele $
 *
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#ifndef _FUTURE_H_
#define _FUTURE_H_

#include <stdint.h>
#include <semaphore.h>
#include <conf.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* define states */
#define BLOCK 0
#define READY 1

/* Future state definitions */
//#define FFREE 0x03 /**< this future is free */
//#define FUSED 0x04 /**< this future is used */

/* type definition of "future" */
typedef unsigned int future;

/**
 * Future table entry
 */
struct futent {
   int state;
   future f;
};

extern struct futent futab[];

int futureMain(void);
future future_alloc(int future_flags);
syscall future_free(future);
syscall future_get(future, int*);
syscall future_set(future, int);
void future_prod(void);
void future_cons(void);

#endif // _FUTURE_H_