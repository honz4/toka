/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: quotes.c
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
#include <memory.h>

#include "toka.h"

#define ON -1
#define OFF 0

extern long compiler;
extern long stack[], sp;
extern long rstack[], rsp;
extern Inst *heap, *ip;



/******************************************************
 *|F| Variables:
 *|F|   QUOTE quotes[8]
 *|F|   Holds details about the compiler state, heap,
 *|F|   etc for quotes during compilation.
 *|F|
 *|F|   long qdepth
 *|F|   Tracks how deeply the quotes are nested
 *|F|
 *|F|   long quote_counter
 *|F|   Tracks the current loop index
 *|F|
 *|F|   Inst top
 *|F|   Holds a pointer to the root quote
 *|F|
 ******************************************************/
typedef struct
{
  Inst heap;
  long compiler;
} QUOTE;

QUOTE quotes[8];
long qdepth = 0, quote_counter = 0;
Inst top;


/******************************************************
 *|G| [        ( -a )      Create a new quote
 *
 *|F| begin_quote()
 *|F| Create a new quote. This allocates space for it,
 *|F| and sets the compiler flag. A pointer to the
 *|F| quote's start is pushed to the stack.
 *|F|
 ******************************************************/
void begin_quote()
{
  quotes[qdepth].heap = (Inst)heap;
  quotes[qdepth].compiler = compiler;
  qdepth++;

  heap = gc_alloc(64, sizeof(Inst), GC_MEM);
  push((long)heap);

  if (qdepth == 1)
    top = (Inst)heap;
  compiler = ON;
}


/******************************************************
 *|G| ]        ( - )       Close an open quote
 *
 *|F| end_quote()
 *|F| Terminate the previously opened quote and perform
 *|F| data_class() semantics.
 *|F|
 ******************************************************/
void end_quote()
{
  *heap++ = (Inst)0;
  qdepth--;
  heap = (Inst *)quotes[qdepth].heap;
  compiler = quotes[qdepth].compiler;
  if (compiler == ON)
  {
    *heap++ = (Inst)&qlit;
    *heap++ = (Inst)TOS; DROP;
  }
}


/******************************************************
 *|G| invoke   ( a- )      Execute a quote
 *
 *|F| invoke()
 *|F| Call a quote (passed on TOS)
 *|F|
 ******************************************************/
void invoke()
{
  Inst *foo;

  foo = (Inst *)TOS; DROP;
  rstack[rsp] = (long)ip;
  rsp++;
  vm_run(foo);
  rsp--;
  ip = (Inst *)rstack[rsp];
}


/******************************************************
 *|G| iterate  ( na- )     Execute a quote 'n' times
 *
 *|F| iterate()
 *|F| Repeat execution of a quote (passed on TOS), NOS
 *|F| number of times.
 *|F|
 ******************************************************/
void iterate()
{
  long count, old_counter;
  Inst quote;

  quote = (Inst)TOS; DROP;
  count = TOS; DROP;
  old_counter = quote_counter;
  
  rstack[rsp] = (long)ip;
  rsp++;

  for(;count > 0; count--)
  {
    quote_counter = count;
    vm_run((Inst *)quote);
  }
  quote_counter = old_counter;

  rsp--;
  ip = (Inst *)rstack[rsp];
}


/******************************************************
 *|G| t/f      ( fab- )    Invoke 'a' if 'f' flag is
 *|G|                      true, 'b' if false.
 *
 *|F| truefalse()
 *|F| Takes three items (true-xt, false-xt, and a flag)
 *|F| from the stack. Stack should be passed in as:
 *|F|   flag true false 
 *|F| It will execute true if the flag is true, false
 *|F| otherwise.
 *|F|
 ******************************************************/
void truefalse()
{
  Inst true, false;
  long flag;

  false = (Inst)TOS; DROP;
  true = (Inst)TOS; DROP;
  flag = TOS; DROP;

  if (flag == -1)
    push((long)true);
  else
    push((long)false);

  invoke();
}


/******************************************************
 *|G| recurse  ( - )       Compile a call to the top
 *|G|                      quote.
 *
 *|F| recurse()
 *|F| Compiles a call to the top-level quote. As a
 *|F| trivial example:
 *|F|   [ dup 1 > [ dup 1 - recurse swap 2 - recurse + ] true? ] is fib
 *|F| 
 ******************************************************/
void recurse()
{
  push((long)top);
  quote_forth_class();
}


/******************************************************
 *|F| qlit()
 *|F| Push the value in the following memory location
 *|F| to the stack. This is used instead of lit() so
 *|F| that the decompiler (and eventually debugger) can
 *|F| reliably identify nested quotes as opposed to 
 *|F| regular literals.
 *|F| 
 ******************************************************/
void qlit()
{
  sp++;
  TOS = (long)*ip;
  ip++;
}
           

/******************************************************
 *|G| i        ( -n )      Return the current loop index
 *
 *|F| quote_index()
 *|F| Return the current loop index (counter)
 *|F| 
 ******************************************************/
void quote_index()
{
  push(quote_counter);
}
