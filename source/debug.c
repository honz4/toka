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
extern long stack[], sp, rsp, last, base;
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
 *|G| :stat    (  -  )     Display information about
 *|G|                      the virtual machine status
 *
 *|F| vm_info()
 *|F| Display information about Toka's memory use,
 *|F| dictionary, etc.
 *|F|
 ******************************************************/
void vm_info()
{
  long a, permanent_objects, permanent_size;
  long size = 0, tsize = 0;

  for (a = 0; a != gc_depth; a++)
    size += gc_list[a].size;
  for (a = 0; a != gc_tdepth; a++)
    tsize += gc_trash[a].size;

  permanent_objects = gc_objects - gc_depth - gc_tdepth;
  permanent_size = gc_used - size - tsize;

  a = (sizeof(GCITEM) * 128)*2;
  printf("-- Memory Use -------------------------------\n");
  printf("  %lu KiB (%lu) used for bookkeeping\n", a/1024, a);
  printf("  Permanent Allocations:\n");
  printf("    %lu objects totaling %lu KiB (%lu)\n", permanent_objects, permanent_size/1024, permanent_size);
  printf("  Temporary Allocations:\n");
  printf("    User:   %lu objects totaling %lu KiB (%lu)\n", gc_depth, size/1024, size);
  printf("    System: %lu objects totaling %lu KiB (%lu)\n", gc_tdepth, tsize/1024, tsize);
  printf("-- Dictionary -------------------------------\n");
  printf("  %lu named items (Max: %lu)\n", last, (long)MAX_DICTIONARY_ENTRIES);
  printf("-- Stacks -----------------------------------\n");
  printf("  Data: %lu items (Max: %lu)\n", sp, (long)MAX_DATA_STACK);
  printf("  Return: %lu items (Max: %lu)\n", rsp, (long)MAX_RETURN_STACK);
  printf("---------------------------------------------\n");
}
