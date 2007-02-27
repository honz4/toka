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
extern long stack[], sp, last;
extern long gc_used, gc_objects, gc_depth, gc_tdepth;
extern ENTRY dictionary[];
extern GCITEM gc_list[];
extern GCITEM gc_trash[];



/******************************************************
 *|G| :words   ( - )       Display a list of all named
 *|G|                      quotes and data
 *
 *|F| words()
 *|F| Display a list of all named words
 *|F|
 ******************************************************/
void words()
{
  long primitives, data, quotes;
  long a;

  primitives = 0; data = 0; quotes = 0;

  printf("Primitives:\n");
  for(a = last-1; a >= 0; a--)
  {
    if (dictionary[a].class == &forth_class || dictionary[a].class == &self_class)
    {
      printf("%s ", dictionary[a].name);
      primitives++;
    }
  }

  printf("\n\nQuotes:\n");
  for(a = last-1; a >= 0; a--)
  {
    if (dictionary[a].class == &quote_forth_class || dictionary[a].class == &quote_macro_class)
    {
      printf("%s ", dictionary[a].name);
      quotes++;
    }
  }

  printf("\n\nData:\n");
  for(a = last-1; a >= 0; a--)
  {
    if (dictionary[a].class == &data_class)
    {
      printf("%s ", dictionary[a].name);
      data++;
    }
  }

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
  printf("<%li> ", sp);
  for(a = 1; a <= sp; a++)
  {
    printf("%li ", stack[a]);
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

  for(a = 0; a != gc_depth; a++)
    size += gc_list[a].size;
  for(a = 0; a != gc_tdepth; a++)
    tsize += gc_trash[a].size;

  a = (sizeof(GCITEM) * 128)*2;
  printf("gc: %li KiB (%li bytes) used for bookkeeping\n", a/1024, a);
  printf("gc: %li objects totaling %li KiB (%li bytes)\n", gc_objects, gc_used/1024, gc_used);
  printf("gc: Temporary:  %li (%li KiB, %li bytes)\n", gc_depth, size/1024, size);
  printf("gc: Trash:      %li (%li KiB, %li bytes)\n", gc_tdepth, tsize/1024, tsize);
}
