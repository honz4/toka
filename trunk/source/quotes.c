/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: quotes.c
 *|F|
 *
 * Copyright (c) 2006, 2007  Charles R. Childers
 *
 * Permission to use, copy, modify, and distribute this 
 * software for any purpose with or without fee is hereby 
 * granted, provided that the above copyright notice and 
 * this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR 
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE 
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL 
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF 
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING 
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "toka.h"

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

  heap = gc_alloc(MAX_QUOTE_SIZE, sizeof(Inst), GC_MEM);
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
  long size;

  *heap++ = (Inst)0;
  push((long)heap);

  size = (TOS - NOS) / sizeof(Inst); DROP;
  if (size > MAX_QUOTE_SIZE)
    error(ERROR_QUOTE_TOO_BIG);

  qdepth--;
  heap = (Inst *)quotes[qdepth].heap;
  compiler = quotes[qdepth].compiler;

  if (COMPILING)
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
 *|G| compile  ( a- )      Compile a call to the quote
 *
 *|F| compile()
 *|F| Compile the code needed to call a quote (passed on TOS)
 *|F|
 ******************************************************/
void compile()
{
  gc_keep();
  *heap++ = &quote_class;
  *heap++ = (Inst)TOS; DROP;
}


/******************************************************
 *|G| countedLoop ( ulq- ) Execute a quote a set number
 *|G|                      of times, updating the 'i'
 *|G|                      counter each time.
 *
 *|F| countedLoop()
 *|F| Execute a quote a given number of times. You pass
 *|F| a quote, and upper/lower limits. The loop counter,
 *|F| 'i', is updated with each cycle.
 *|F|
 ******************************************************/
void countedLoop()
{
  long upper, lower, count, old_counter;
  Inst quote;

  quote = (Inst)TOS; DROP;
  lower = TOS; DROP;
  upper = TOS; DROP;

  old_counter = quote_counter;
  rstack[rsp] = (long)ip;
  rsp++;

  if (upper < lower)
  {
    for (count = upper; count < lower; count++)
    {
      quote_counter = count;
      vm_run((Inst *)quote);
    }
  }

  if (lower < upper)
  {
    for (count = upper; count > lower; count--)
    {
      quote_counter = count;
      vm_run((Inst *)quote);
    }
  }

  quote_counter = old_counter;
  rsp--;
  ip = (Inst *)rstack[rsp];
}


/******************************************************
 *|G| ifTrueFalse ( fab- ) Invoke 'a' if 'f' flag is
 *|G|                      true, 'b' if false.
 *
 *|F| truefalse()
 *|F| Takes three items (true-xt, false-xt, and a flag)
 *|F| from the stack. Stack should be passed in as:
 *|F|   flag true false 
 *|F| It will execute true if the flag is true, or false
 *|F| if the flag is false. If the flag is not true
 *|F| or false, neither quote will be executed.
 *|F|
 ******************************************************/
void truefalse()
{
  Inst true, false;
  long flag;

  false = (Inst)TOS; DROP;
  true = (Inst)TOS; DROP;
  flag = TOS; DROP;

  if (flag == TRUE)
    push((long)true);

  if (flag == FALSE)
    push((long)false);

  if (flag == TRUE || flag == FALSE)
    invoke();
}


/******************************************************
 *|G| recurse  ( - )       Compile a call to the top
 *|G|                      quote.
 *
 *|F| recurse()
 *|F| Compiles a call to the top-level quote. As a
 *|F| trivial example:
 *|F|   [ dup 1 > [ dup 1 - recurse swap 2 - recurse + ] ifTrue ] is fib
 *|F| 
 ******************************************************/
void recurse()
{
  push((long)top);
  quote_word_class();
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
  push((long)*ip);
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


/******************************************************
 *|G| whileTrue  ( a- )    Execute quote. If the quote
 *|G|                      returns TRUE, execute again.
 *|G|                      otherwise end the cycle.
 *
 *|F| quote_while_true()
 *|F| Return execution of a quote until the quote
 *|F| returns FALSE.
 *|F| 
 ******************************************************/
void quote_while_true()
{
  Inst quote;
  long flag;

  quote = (Inst)TOS; DROP;
  flag = TRUE;

  while (flag == TRUE)
  {
    rstack[rsp] = (long)ip;   rsp++;
    vm_run((Inst *)quote);
    flag = TOS; DROP;
    rsp--; ip = (Inst *)rstack[rsp];
  }
}


/******************************************************
 *|G| whileFalse ( a- )    Execute quote. If the quote
 *|G|                      returns TRUE, execute again.
 *|G|                      otherwise end the cycle.
 *
 *|F| quote_while_false()
 *|F| Return execution of a quote until the quote
 *|F| returns TRUE.
 *|F| 
 ******************************************************/
void quote_while_false()
{
  Inst quote;
  long flag;

  quote = (Inst)TOS; DROP;
  flag = FALSE;

  while (flag == FALSE)
  {
    rstack[rsp] = (long)ip;   rsp++;
    vm_run((Inst *)quote);
    flag = TOS; DROP;
    rsp--; ip = (Inst *)rstack[rsp];
  }
}
