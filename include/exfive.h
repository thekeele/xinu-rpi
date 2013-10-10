/*
 * @file exfive.h
 *
 * $Id: exfive.h 1337 2013-09-25 11:11:11Z mkeele $
 *
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#ifndef _EXFIVE_H_
#define _EXFIVE_H_

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <semaphore.h>

void exfive(void);
void producer(semaphore, semaphore);
void consumer(semaphore, semaphore);

#endif                          /* _EXFIVE_H_ */
