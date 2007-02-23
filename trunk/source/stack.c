/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: stack.c
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
extern long stack[], rstack[], sp, rsp;


/******************************************************
 *|G| dup      ( n-nn )    Duplicate the TOS
 *
 *|F| stack_dup()
 *|F| Duplicate the TOS
 *|F|
 ******************************************************/
void stack_dup()
{
  stack[sp+1] = TOS;
  sp++;
}


/******************************************************
 *|G| drop     ( n- )      Drop the TOS
 *
 *|F| stack_drop()
 *|F| Drop the TOS
 *|F|
 ******************************************************/
void stack_drop()
{
  sp--;
}


/******************************************************
 *|G| swap     ( ab-ba )   Exchange the TOS and NOS
 *
 *|F| stack_swap()
 *|F| Exchange TOS and NOS
 *|F|
 ******************************************************/
void stack_swap()
{
  long a, b;
  a = TOS;    b = NOS;
  TOS = b;    NOS = a;
}


/******************************************************
 *|G| >r       ( n- )      Push TOS to return stack, DROP
 *
 *|F| stack_to_r()
 *|F| Push TOS to return stack, DROP TOS
 *|F|
 ******************************************************/
void stack_to_r()
{
  TORS = TOS; DROP; rsp++;
}


/******************************************************
 *|G| r>       ( -n )      Pop TORS to the data stack
 *
 *|F| stack_from_r()
 *|F| Pop TORS to the data stack
 *|F|
 ******************************************************/
void stack_from_r()
{
  rsp--; stack_dup(); TOS = TORS; 
}


/******************************************************
 *|G| depth    ( -n )      Return the number of items
 *|G|                      on the stack
 *
 *|F| stack_depth()
 *|F| Return the number of items on the stack
 *|F|
 ******************************************************/
void stack_depth()
{
  long items = sp;
  push(items);
}
