/**
* @file future.c
*
* @author mkeele@indiana.edu Mark Keele | fediaz@indiana.edu Franklin Diaz
*
* @date 10/31/13
*/
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#include <future.h> 

int32_t number = 7; /* number assigned with an initial value */
int32_t value = 0; /* future value */
struct futent futures[3]; /* array of structs for each future */

/**
* future -- producer and consumer processes synchronized with semaphores
* @param void
*/
void futureMain(void)
{
  semaphore cons, prod;

  cons = semcreate(0);
  prod = semcreate(1);

  future f1, f2, f3;  //future variables

  // allocate three futures
  f1 = future_alloc(0);
  f2 = future_alloc(1);
  f3 = future_alloc(2);

  // create consumers & producers
  resume( create(future_cons, 1024, 20, "fcons1", 3, f1, cons, prod) );
  resume( create(future_prod, 1024, 20, "fprod1", 3, f1, cons, prod) );
  resume( create(future_cons, 1024, 20, "fcons2", 3, f2, cons, prod) );
  resume( create(future_prod, 1024, 20, "fprod2", 3, f2, cons, prod) );
  resume( create(future_cons, 1024, 20, "fcons3", 3, f3, cons, prod) );
  resume( create(future_prod, 1024, 20, "fprod3", 3, f3, cons, prod) );

  // tear down the futures
  future_free(f1);
  future_free(f2);
  future_free(f3);
}

/*
* using the future_flags as an index
*/
future future_alloc(int future_flags){
  futures[future_flags].state = USED;
  futures[future_flags].fcount = future_flags;
  futures[future_flags].fstate = NOT_COMPLETE;
  return future_flags;
}

/* sets state of future to FREE */
syscall future_free(future f){
  futures[f].state = FREE;
  return OK;
}

/* if future has value return */
syscall future_get(future f){
  if (futures[f].fstate == COMPLETE_SUCCESS)
  {
    futures[f].fstate = DONE; 
    value = futures[f].result;
    return OK;
  }
  return SYSERR;
}

/* if future does not have value set */
syscall future_set(future f, int i) {
  if (futures[f].fstate == NOT_COMPLETE)
  {
    futures[f].result = i;
    futures[f].fstate = COMPLETE_SUCCESS; 
    return OK; 
  } 
  return SYSERR;
}

/**
* produce -- provides a value to future
* @param future, cons/prod semaphores
*/
void future_prod(future f, semaphore consumed, semaphore produced)
{
  int myResult = SYSERR;
  
  while (myResult != OK)
  {
    wait(consumed);
    myResult = future_set(f,number);
    number++;
    signal(produced);
  }
}

/**
* consume -- gets a value from a future
* @param future, cons/prod semaphores
*/
void future_cons(future f, semaphore consumed, semaphore produced)
{
  int myResult = SYSERR; 

  while (myResult != OK)
  {
    wait(produced);
    myResult = future_get(f);
    printf("Future-> flag: %d, fstate: %d, state: %d, value: %d\n", futures[f].fcount, futures[f].fstate, futures[f].state, value);
    signal(consumed);
  }
}