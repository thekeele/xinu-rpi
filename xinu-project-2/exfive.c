/**
 * @file exfive.c
 * @provides producer and consumer with semaphores
 *    
 * $Id: exfive.c 1337 2013-09-25 11:11:1Z mkeele $
 */
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

#include <exfive.h>
#include <stdint.h>
#include <semaphore.h>

void producer(semaphore, semaphore), consumer(semaphore, semaphore);

static int32_t n = 0; /* n assigned an initial value of zero */

/**
 * exfive -- producer and consumer processes synchronized with semaphores
 * @param void
 */
void exfive(void)
{
  semaphore produced, consumed;
  
  consumed = semcreate(0);
  produced = semcreate(1);
  
  resume( create(consumer, 1024, 20, "cons", 2, consumed, produced) );
  resume( create(producer, 1024, 20, "prod", 2, consumed, produced) );
}

/**
 * produce -- increment n 2000 times, waiting for it to be consumed
 * @param consumed, produced semaphores
 */
void producer(semaphore consumed, semaphore produced)
{
  int32_t i;

  for( i=1 ; i<=20; i++ ) {
    wait(consumed);
    n++;
    signal(produced);
  }
}

/**
 * consume -- print n 2000 times, waiting for it to be produced
 * @param consumed, produced semaphores
 */
void consumer(semaphore consumed, semaphore produced)
{
  int32_t i;
  
  for( i=1 ; i<=20; i++ ) {
    wait(produced);
    printf("n is %d \n", n);
    signal(consumed);
  }
}
