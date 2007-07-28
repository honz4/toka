#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "toka.h"

extern Inst *ip;
extern long sp, rsp, stack[], rstack[];

#ifdef SIGNALS
void trap_signals()
{
  signal(SIGINT,  caught_signal);
  signal(SIGFPE,  caught_signal);
  signal(SIGSEGV, caught_signal);
  signal(SIGILL,  caught_signal);
}

void caught_signal(int which)
{
  long a;

  sigrelse(SIGINT);
  sigrelse(SIGFPE);
  sigrelse(SIGSEGV);
  sigrelse(SIGILL);

  signal(SIGINT,  caught_signal);
  signal(SIGFPE,  caught_signal);
  signal(SIGSEGV, caught_signal);
  signal(SIGILL,  caught_signal);

  for (a = 0; a < 60; a++)
    putchar('*');

  printf(" SIGNAL CAUGHT\n");
  printf("Signal: ");
  switch(which)
  {
    case SIGINT:  printf("SIGINT\n");  break;
    case SIGFPE:  printf("SIGFPE\n");  break;
    case SIGSEGV: printf("SIGSEGV\n"); break;
    case SIGILL:  printf("SIGILL\n");  break;
  }

  printf("\nIP: %li\n", (long)ip);

  printf("Data Stack:   ");  display_stack();
  printf("Return Stack: <%li> ", rsp);

  for (a = 0; a < rsp; a++)
  {
    push(rstack[a]);
    dot();
  }
  putchar('\n');

  ip = 0; rsp = 0; sp = 0;

  for (a = 0; a < 60; a++)
    putchar('*');

  putchar('\n');

  interpret();
}
#endif
