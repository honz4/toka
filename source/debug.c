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
 *|F| long display_names_by_class(void *class)
 *|F| Display a list of all named items with the 
 *|F| specified class. Returns the number of named 
 *|F| items displayed.
 *|F|
 ******************************************************/
long display_names_by_class(void *class)
{
  long names, a;

  names = 0;

  for (a = last-1; a >= 0; a--)
  {
    if (dictionary[a].class == class)
    {
      printf("%s ", dictionary[a].name);
      names++;
    }
  }

  return names;
}



/******************************************************
 *|G| :names   ( - )       Display a list of all named
 *|G|                      quotes and data
 *
 *|F| names()
 *|F| Display a list of all named items
 *|F|
 ******************************************************/
void names()
{
  long primitives, data, quotes;

  primitives = 0; data = 0; quotes = 0;

  printf("Primitives:\n");
  primitives = display_names_by_class(&macro_class);
  primitives += display_names_by_class(&forth_class);

  printf("\n\nQuotes:\n");
  quotes = display_names_by_class(&quote_macro_class);
  quotes = display_names_by_class(&quote_forth_class);

  printf("\n\nData:\n");
  data = display_names_by_class(&data_class);

  printf("\n\nTotal: %li.\n", last);
  printf(" - %li primitives.\n", primitives);
  printf(" - %li quotes.\n", quotes);
  printf(" - %li data.\n", data);
}



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
  printf("gc: %lu objects totaling %lu KiB (%lu)\n", gc_objects, gc_used/1024, gc_used);
  printf("gc: User:   %lu KiB (%lu) in %lu objects\n", size/1024, size, gc_depth);
  printf("gc: System: %lu KiB (%lu) in %lu objects\n", tsize/1024, tsize, gc_tdepth);
}
