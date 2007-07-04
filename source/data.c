/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: data.c
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
extern Inst *heap;
extern long stack[], sp;


/******************************************************
 *|G| #        ( n- )      Push the following cell to
 *|G|                      the stack.
 *
 *|F| make_literal()
 *|F| Compile a call to lit() and then place TOS into
 *|F| the next memory location.
 *|F|
 ******************************************************/
void make_literal()
{
  gc_keep();
  *heap++ = (Inst)&lit;
  *heap++ = (Inst)TOS; 
  DROP;
}


/******************************************************
 *|G| $#       ( n- )      Push the following cell to
 *|G|                      the stack.
 *
 *|F| make_string_literal()
 *|F| Compile a call to string_lit() and then place TOS 
 *|F| into the next memory location.
 *|F|
 ******************************************************/
void make_string_literal()
{
  gc_keep();
  *heap++ = (Inst)&string_lit;
  *heap++ = (Inst)TOS; 
  DROP;
}


/******************************************************
 *|G| @        ( a-n )     Fetch the value in memory
 *|G|                      location 'a'
 *
 *|F| fetch()
 *|F| Fetch the value in the memory location pointed to
 *|F| by TOS.
 *|F|
 ******************************************************/
void fetch()
{
  TOS = *(long *)TOS;
}


/******************************************************
 *|G| !        ( na- )     Store 'n' to memory location
 *|G|                      'a'
 *
 *|F| store()
 *|F| Store NOS into the memory location specified by
 *|F| TOS.
 *|F|
 ******************************************************/
void store()
{
  *(long *)TOS = NOS; DROP; DROP;
}


/******************************************************
 *|G| c@        ( a-n )    Fetch a byte from memory
 *|G|                      location 'a'
 *
 *|F| fetch_char()
 *|F| Fetch the value in the memory location pointed to
 *|F| by TOS. This version reads a single byte.
 *|F|
 ******************************************************/
void fetch_char()
{
  TOS = *(char *)TOS;
}


/******************************************************
 *|G| c!        ( na- )    Store byte 'n' to memory
 *|G|                      location 'a'
 *
 *|F| store_char()
 *|F| Store NOS into the memory location specified by
 *|F| TOS. This version stores a single byte.
 *|F|
 ******************************************************/
void store_char()
{
  *(char *)TOS = (char)NOS; DROP; DROP;
}


/******************************************************
 *|G| copy     ( sdc- )    Copy 'c' bytes from 's' to
 *|G|                      'd'
 *
 *|F| copy()
 *|F| Copies 'count' bytes from 'source' to 'dest'. The
 *|F| stack form for this is:
 *|F|   source dest count
 *|F| The memory locations can overlap.
 *|F|
 ******************************************************/
void copy()
{
  long count, *dest, *source;
  count = TOS; DROP;
  dest = (long *)TOS; DROP;
  source = (long *)TOS; DROP;
  memmove(dest, source, count);
}


/******************************************************
 *|G| cell-size ( -n )     Return the size of a cell
 *
 *|F| cell_size()
 *|F| Push the size of a cell to the stack.
 *|F|
 ******************************************************/
void cell_size()
{
  push((long)sizeof(long));
}


/******************************************************
 *|G| char-size ( -n )     Return the size of a char
 *
 *|F| char_size()
 *|F| Push the size of a char to the stack
 *|F|
 ******************************************************/
void char_size()
{
  push((long)sizeof(char));
}
