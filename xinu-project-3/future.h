/* 
 * @file future.h - main, produce, consume 
 *
 * @author mkeele@indiana.edu Mark Keele | fediaz@indiana.edu Franklin Diaz
 *
 * @date 10/31/13
 * 
 * future_t is a special type of integer. We will create an asynch 
 * function that looks like a thread and eventually creates a value. 
 * things happen depending on future value. 
 *
 * This project is to implement futures in Xinu. Also, write a design 
 * document (at least a page) describing implementation considerations.

 * Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#ifndef _FUTURE_H_
#define _FUTURE_H_

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <semaphore.h>

/* Future state definitions 

A Future is an object holding a value which may become available 
at some point. This value is usually the result of some other computation:

If the computation has not yet completed, we say that the Future 
is not completed.  If the computation has completed with a value or 
with an exception, we say that the Future is completed.
Completion can take one of two forms:

When a Future is completed with a value, we say that the future was 
successfully completed with that value. When a Future is completed with 
an exception thrown by the computation, we say that the Future was 
failed with that exception.

*/
#define FREE             0
#define USED             1
#define NOT_COMPLETE     2  // ready to be called by setter
#define COMPLETE_SUCCESS 3  // ready to be called by getter
#define COMPLETE_FAIL    4  // something went wrong
#define DONE             5  // done, ready to be free'd

/* type definition of "future" */
typedef unsigned int future;

/* Each entry in futureTable corresponds to one future 
 * See 7.7 in the book
 */
struct futent {
   int fstate;  // NOT_COMPLETE, COMPLETE_SUCCESS, COMPLETE_FAIL, DONE
   int fcount;  // count for the future  
   int state;   // FREE, USED
   int result;  // holds a value
};

void futureMain(void);
future future_alloc(int future_flags);
syscall future_free(future);
syscall future_get(future); // means this is an "explicit" future
syscall future_set(future, int);
void future_prod(future, semaphore, semaphore);
void future_cons(future, semaphore, semaphore);

#endif
