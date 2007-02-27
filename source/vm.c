/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: vm.c
 *|F| 
 *
 * Copyright (C) 2007 Charles R. Childers
 * Distributed under the terms of the MIT/X11 License
 * (see doc/LICENSE for full terms)
 *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "toka.h"

/******************************************************
 *|F| Variables:
 *|F|   Inst *heap
 *|F|   Pointer into the current heap
 *|F|
 *|F|   Inst *ip
 *|F|   The instruction pointer
 *|F|
 *|F|   long stack[100], rstack[100]
 *|F|   The data and return stacks
 *|F|
 *|F|   long sp, rsp
 *|F|   The stack pointers
 *|F|
 ******************************************************/
Inst *heap, *ip;
long stack[100], rstack[1024];
long sp = 0, rsp = 0;


/******************************************************
 *|F| vm_run(Inst)
 *|F| Run through a list of instructions
 *|F| Side effects:
 *|F|   modifes *ip
 *|F|
 ******************************************************/
void vm_run(Inst prog[])
{
  ip = prog;
  while (*ip != 0)
  {
    vm_stack_check();
    ((*ip++)());
  }
}


/******************************************************
 *|F| vm_stack_check()
 *|F| Check for over/underflow and reset if detected
 *|F| If the return stack over/underflows, exit Toka
 *|F| 
 ******************************************************/
void vm_stack_check()
{
  if (sp < 0 || sp > 127)
  {
    printf("vm: stack problem (sp=%li); aborting!\n", sp);
    exit(1);
  }
  if (rsp < 0 || rsp > 1023)
  {
    printf("vm: return stack problem (rsp=%li); aborting!\n", rsp);
    exit(1);
  }
}


/******************************************************
 *|F| push(long a)
 *|F| Push a number to the stack.
 *|F|
 ******************************************************/
void push(long a)
{
  sp++; TOS = a;
}


/******************************************************
 *|F| lit()
 *|F| Push the value in the following memory location
 *|F| to the stack
 *|F|
 ******************************************************/
void lit()
{
  sp++;
  TOS = (long)*ip;
  ip++;
}
