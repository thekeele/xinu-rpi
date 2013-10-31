/**
 * @file future.c
 * @provides 
 *    
 * $Id: `future.c 1337 2013-09-25 11:11:1Z mkeele $
 */
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#include <exfive.h>
#include <future.h> 

static int32_t n = 0; /* n assigned an initial value of zero */
future f1, f2, f3;

/**
 * exfive -- producer and consumer processes synchronized with semaphores
 * @param void
 */
int futureMain(void)
{
  /*semaphore produced, consumed;
  
  consumed = semcreate(0);
  produced = semcreate(1);
  
  resume( create(consumer, 1024, 20, "cons", 2, consumed, produced) );
  resume( create(producer, 1024, 20, "prod", 2, consumed, produced) );*/

  printf("future test\n");

  // allocate three futures
  /*f1 = future_alloc(0);
  f2 = future_alloc(0);
  f3 = future_alloc(0);*/

  // create consumers & producers
  /*resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
  resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
  resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
  resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
  resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
  resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );*/

  // tear down the futures
  /*future_free(f1);
  future_free(f2);
  future_free(f3);*/

  return 0;
}

future future_alloc(int future_flags){
   struct futent f;
   f.state = BLOCK;
   return f.f; 

}

syscall future_free(future f){
   
   return OK;
}

syscall future_get(future f){
   return OK;
}

syscall future_set(future f, int i) {
   return OK;
}

/**
 * produce -- 
 * @param 
 */
void future_prod(void/*semaphore consumed, semaphore produced*/)
{
  int32_t i;

  for( i=1 ; i<=2000; i++ ) {
    //wait(consumed);
    n++;
    //signal(produced);
  }
}

/**
 * consume -- 
 * @param 
 */
void future_cons(void/*semaphore consumed, semaphore produced*/)
{
  int32_t i;
  
  for( i=1 ; i<=2000; i++ ) {
    //wait(produced);
    printf("n is %d \n", n);
    //signal(consumed);
  }
  printf("xsh$ ");
}
