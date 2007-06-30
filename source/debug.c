/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: debug.c
 *|F|
 *
 * Copyright (C) 2007 Charles R. Childers
 * Distributed under the terms of the MIT/X11 License
 * (see doc/LICENSE for full terms)
 *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <memory.h>

#include "toka.h"

extern Inst *heap;
extern long stack[], sp, last, base;
extern long gc_used, gc_objects, gc_depth, gc_tdepth;
extern ENTRY dictionary[];
extern GCITEM gc_list[];
extern GCITEM gc_trash[];



/******************************************************
 *|G| :stack   ( - )       Display all values on the
 *|G|                      data stack
 *
 *|F| display_stack()
 *|F| Display all items on the stack.
 *|F|
 ******************************************************/
void display_stack()
{
  long a;

  switch(base)
  {
    case  8: printf("<%lo> ", sp); break;
    case 16: printf("<%lx> ", sp); break;
    default: printf("<%li> ", sp); break;
  }

  for (a = 1; a <= sp; a++)
  {
    push(stack[a]);
    dot();
  }
  printf("\n");
}



/******************************************************
 *|G| :gc      (  -  )     Display information about
 *|G|                      the garbage collection list
 *
 *|F| gc_info()
 *|F| Display information about Toka's memory use
 *|F|
 ******************************************************/
void gc_info()
{
  long a;
  long size = 0, tsize = 0;

  for (a = 0; a != gc_depth; a++)
    size += gc_list[a].size;
  for (a = 0; a != gc_tdepth; a++)
    tsize += gc_trash[a].size;

  a = (sizeof(GCITEM) * 128)*2;
  printf("gc: %lu KiB (%lu) used for bookkeeping\n", a/1024, a);
  printf("    %lu objects totaling %lu KiB (%lu)\n", gc_objects, gc_used/1024, gc_used);
  printf("    User:   %lu KiB (%lu) in %lu objects\n", size/1024, size, gc_depth);
  printf("    System: %lu KiB (%lu) in %lu objects\n", tsize/1024, tsize, gc_tdepth);
}
