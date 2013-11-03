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

//struct futent futures[3]; /* array of structs for each future */

/**
 * future -- producer and consumer processes synchronized with semaphores
 * @param void
 */
void futureMain(void)
{
  semaphore produced, consumed;
  
  consumed = semcreate(0);
  produced = semcreate(1);

  //future f1, f2;

  // allocate three futures
  //f1 = future_alloc(0);
  //f2 = future_alloc(0);
  //f3 = future_alloc(0);

  // create consumers & producers
  resume( create(future_cons, 1024, 20, "fcons1", 2, consumed, produced) );
  resume( create(future_prod, 1024, 20, "fprod1", 2, consumed, produced) );
  resume( create(future_cons, 1024, 20, "fcons2", 2, consumed, produced) );
  resume( create(future_prod, 1024, 20, "fprod2", 2, consumed, produced) );
  /*resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
  resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );*/

  // tear down the futures
  //future_free(f1);
  //future_free(f2);
  //future_free(f3);
}

/*future future_alloc(int future_flags){
   //struct futent f;
   //f.state = BLOCK;
   //f.state = 0;
   return OK; 
}

syscall future_free(future f){
  //ff.state = 1;
  return OK;
}

syscall future_get(future f){
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
void future_prod(semaphore consumed, semaphore produced)
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
void future_cons(semaphore consumed, semaphore produced)
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
