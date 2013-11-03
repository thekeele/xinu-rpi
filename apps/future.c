/**
 * @file future.c
 *
 * @author mkeele@indiana.edu Mark Keele | fediaz@indiana.edu Franklin Diaz
 *
 * @date 10/31/13
 */
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#include <future.h> 

int32_t number = 0; /* number assigned an initial value of zero */
struct futent futures[3]; /* array of structs for each future */

/**
 * future -- producer and consumer processes synchronized with semaphores
 * @param void
 */
void futureMain(void)
{
  semaphore produced, consumed;
  
  consumed = semcreate(0);
  produced = semcreate(1);

  future f1, f2, f3;  //future variables
  int ff1, ff2, ff3;  //future flag variables

  // allocate three futures
  ff1 = future_alloc(0);
  printf("allocate f1: %d\n", ff1);
  ff2 = future_alloc(1);
  printf("allocate f2: %d\n", ff2);
  ff3 = future_alloc(2);
  printf("allocate f3: %d\n", ff3);

  // create consumers & producers
  resume( create(future_cons, 1024, 20, "fcons1", 3, f1, consumed, produced) );
  resume( create(future_prod, 1024, 20, "fprod1", 3, f1, consumed, produced) );
  resume( create(future_cons, 1024, 20, "fcons2", 3, f2, consumed, produced) );
  resume( create(future_prod, 1024, 20, "fprod2", 3, f2, consumed, produced) );
  resume( create(future_cons, 1024, 20, "fcons3", 3, f3, consumed, produced) );
  resume( create(future_prod, 1024, 20, "fprod3", 3, f3, consumed, produced) );

  // tear down the futures
  future_free(f1);
  future_free(f2);
  future_free(f3);
}

/*
 * using the future_flags as an index
 */
future future_alloc(int future_flags){
   futures[future_flags].fstate =  S_USED;
   futures[future_flags].fcount =  future_flags;
   futures[future_flags].state  =  NOT_COMPLETE;
   return future_flags;
}

syscall future_free(future f){
   futures[f].fstate = S_FREE;
   return OK;
}

/*syscall future_get(future f){
  //wait for ready state(*i)
  //return future value(f)
  return OK;
}

syscall future_set(future f, int i) {
  //set future value(f)
  //set state value(i) to ready
  return OK;
}*/

/**
 * produce -- 
 * @param 
 */
void future_prod(future f, semaphore consumed, semaphore produced)
{
  int32_t i;

  for( i=1 ; i<=10; i++ ) {
    wait(consumed);
    number++;
    signal(produced);
  }
  //future_set(f, i);
}

/**
 * consume -- 
 * @param 
 */
void future_cons(future f, semaphore consumed, semaphore produced)
{
  int32_t i;
  
  //future_value = future_get(f, *i);

  for( i=1 ; i<=10; i++ ) {
    wait(produced);
    printf("n is %d \n", number);
    signal(consumed);
  }
  //printf("future_value: %d", future_value);
}
