/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: gc.c
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

#include "toka.h"

extern long stack[], sp;


/******************************************************
 *|F| Variables:
 *|F|   GCITEM gc_list[128]
 *|F|   Holds the list of items marked as garbage
 *|F|
 *|F|   long gc_depth
 *|F|   A pointer to the top of the garbage collection
 *|F|   list
 *|F|
 *|F|   GCITEM gc_trash[128]
 *|F|   Holds the short list of items marked as garbage
 *|F|
 *|F|   long gc_tdepth
 *|F|   A pointer to the top of the short garbage
 *|F|   collection list
 *|F|
 *|F|   long gc_used
 *|F|   Contains the total size of all currently used
 *|F|   memory, including permanent quotes.
 *|F|
 *|F|   long gc_objects
 *|F|   Contains the total number of objects that are
 *|F|   currently existing, including permanent ones.
 *|F|
 ******************************************************/
long gc_used = 0, gc_objects = 0;
GCITEM gc_list[128];  long gc_depth = 0;
GCITEM gc_trash[128]; long gc_tdepth = 0;



/******************************************************
 *|F| gc_alloc(long items, long size, long type)
 *|F| Allocate the requested memory and add it to the
 *|F| garbage collection list.
 *|F| If type is set to 0, add to the normal garbage
 *|F| collection list. If set to 1, add to the short
 *|F| list of known garbage items which can be safely
 *|F| freed at the next gc().
 *|F| If the allocation fails, gc() is called, and the
 *|F| allocation is retried. If it still fails, an
 *|F| error is reported and Toka is terminated.
 *|F|
 ******************************************************/
void *gc_alloc(long items, long size, long type)
{
  void *memory;

  /* If the allocation lists are full, perform */
  /* a collection before proceeding.           */
  if (gc_depth == 127 || gc_tdepth == 127)
    gc();

  memory  = calloc((int)items, (int)size);

  /* If the allocation failed, collect garbage */
  /* and try again.                            */
  if (memory == NULL)
  {
    gc();
    memory = calloc((int)items, (int)size);
    if (memory == NULL)
    {
      printf("gc: out of memory; aborting.\n");
      exit(1);
    }
  }

  /* Leave the allocated memory in a known state */
  memset(memory, 0, size * items);

  /* And finally, update the lists with the allocation */
  if (type == GC_MEM)
  {
    gc_list[gc_depth].xt = (Inst)memory;
    gc_list[gc_depth].size = size * items;
    gc_depth++;
  } 
  else 
  {
    gc_trash[gc_tdepth].xt = (Inst)memory;
    gc_trash[gc_tdepth].size = size * items;
    gc_tdepth++;
  }

  gc_used += size * items;
  gc_objects++;

  return memory;
}



/******************************************************
 *|G| keep     ( a-a )     Mark quotes/allocated memory
 *|G|                      as permanent.
 *
 *|F| gc_keep()
 *|F| Remove the specified address (and any childern it
 *|F| has registered) from the garbage collection list.
 *|F| If the TOS is not an allocated address, this will
 *|F| silently ignore it.
 *|F|
 ******************************************************/
void gc_keep()
{
  long a, which;

  Inst item = (Inst)TOS;
  which = -1;

  for(a = 0; a != gc_depth; a++)
  {
    if (gc_list[a].xt == item)
      which = a;
  }

  if (which != -1)
  {
    for(a = gc_depth; a > which; a--)
      gc_depth--;
  }
}



/******************************************************
 *|G| gc       ( - )       Clean the garbage
 *
 *|F| gc()
 *|F| Free the oldest allocations on the garbage list.
 *|F| Will free up to 16 items from each list per
 *|F| call. If there are 16 or less items remaining,
 *|F| this code will leave the allocations alone.
 *|F|
 ******************************************************/
void gc()
{
  long a, b;

  /* Allocations known to be temporary */
  if (gc_tdepth > 16)
  {
    b = gc_tdepth - 16;

    for(a = 0; a != b; a++)
    {
      free(gc_trash[a].xt);
      gc_used -= gc_trash[a].size;
      gc_list[a].xt = 0;
      gc_objects--;
    }

    if (b != gc_tdepth)
    {
      for(a = 0; a != gc_tdepth; a++)
      {
        gc_trash[a].xt = gc_trash[a+b].xt;
        gc_trash[a].size = gc_trash[a+b].size;
      }
    }

    gc_tdepth -= b;
  }

  /* General Allocations  */
  if (gc_depth > 16)
  {
    b = gc_depth - 16;

    for(a = 0; a != b; a++)
    {
      free(gc_list[a].xt);
      gc_used -= gc_list[a].size;
      gc_list[a].xt = 0;
      gc_objects--;
    }

    if (b != gc_depth)
    {
      for(a = 0; a != gc_depth; a++)
      {
        gc_list[a].xt = gc_list[a+b].xt;
        gc_list[a].size = gc_list[a+b].size;
      }
    }

    gc_depth -= b;
  }
}



/******************************************************
 *|G| malloc   ( n-a )     Allocate 'n' bytes of memory
 *
 *|F| toka_malloc()
 *|F| Allocate TOS bytes of memory. Returns a pointer to
 *|F| the allocated memory.
 *|F|
 ******************************************************/
void toka_malloc()
{
  long size = TOS;
  TOS = (long)gc_alloc(size, sizeof(char), GC_MEM);
}
