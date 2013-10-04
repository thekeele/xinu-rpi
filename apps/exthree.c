/* ex3.c - main, sndch */
#include <exthree.h>

void sndch(char);

/*------------------------------------------------------------------------
 * * main -- example of 2 processes executing the same code concurrently
 * *------------------------------------------------------------------------
 * */
void exthree(void)
{
  resume( create(sndch, 1024, 20, "send A", 1, "A") );
  resume( create(sndch, 1024, 20, "send B", 1, "B") );
}

/*------------------------------------------------------------------------
 * * sndch -- output a character on a serial device indefinitely
 * *------------------------------------------------------------------------
 * */
void sndch(char ch /* character to emit continuously */)
{
  while ( 1 )
    putc(CONSOLE, ch);
}
