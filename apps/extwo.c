/* ex2.c - main, sndA, sndB */
#include <extwo.h>
#include <stdint.h>

void sndA(void), sndB(void);

/*------------------------------------------------------------------------
 * * main -- example of creating processes in Xinu
 * *------------------------------------------------------------------------
 * */
void extwo(void)
{
  resume( create(sndA, 1024, 20, "process 1", 0) );
  resume( create(sndB, 1024, 20, "process 2", 0) );
}

/*------------------------------------------------------------------------
 * * sndA -- repeatedly emit ’A’ on the console without terminating
 * *------------------------------------------------------------------------
 * */
void sndA(void)
{
  int32_t i = 0;
  while( i < 20 ) {
    putc(CONSOLE, "A");
    i++;
  }
}

/*------------------------------------------------------------------------
 * * sndB -- repeatedly emit ’B’ on the console without terminating
 * *------------------------------------------------------------------------
 * */
void sndB(void)
{
  int32_t i = 0;
  while( i < 20 ) {
    putc(CONSOLE, "B");
    i++;
  }
}
