/**
 * @file exfour.c
 * @provides producer and consumer
 *
 * $Id: exfour.c 1337 2013-09-25 11:11:1Z mkeele $
 */
/* Enhanced Xinu, Fakeright (F) 2013.  All rights revoked. */

//#include <xinu.h> //is this needed?
#include <exfour.h>
#include <stdint.h>

void produce(void), consume(void); /* function prototypes */
int32_t n = 0; /* external variables are shared by all processes */

/**
 * xsh_exfour -- spawn unsynchronized producer and consumer processes
 * @param void 
 */
void exfour(void)
{
  resume( create(consume, 1024, 20, "cons", 0) );
  resume( create(produce, 1024, 20, "prod", 0) );
}

/**
 * produce -- enters loop and increments variable 2000 times
 * @param void
 */
void produce(void)
{
  int32_t i;
  
  for( i=1 ; i<=2000 ; i++ )
    n++;
}

/**
 * consume -- enters loop and prints variable 2000 times
 * @param void
 */
void consume(void)
{
  int32_t i;
  
  for( i=1 ; i<=2000 ; i++ )
    printf("The value of n is %d \n", n);
}
