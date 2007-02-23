/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: class.c
 *|F|
 *
 * Copyright (C) 2007 Charles R. Childers
 * Distributed under the terms of the MIT/X11 License
 * (see doc/LICENSE for full terms)
 *
 ******************************************************/

#include "toka.h"

extern long stack[], sp;
extern long compiler, last;
extern Inst *heap;


/******************************************************
 *|F| forth_class()
 *|F| If compiling, compile the xt into the current
 *|F| quote. If interpreting, call the word.
 *|F|
 ******************************************************/
void forth_class()
{
  Inst xt = (Inst)TOS; DROP;
  if(compiler == ON)
    *heap++ = xt;
  else
    ((xt)());
}


/******************************************************
 *|F| self_class()
 *|F| Always call the word
 *|F|
 ******************************************************/
void self_class()
{
  Inst xt = (Inst)TOS; DROP;
  ((xt)());
}


/******************************************************
 *|F| data_class()
 *|F| If compiling, compile a call to lit() and then
 *|F| inline TOS into the following location. Otherwise
 *|F| leave TOS alone.
 *|F|
 ******************************************************/
void data_class()
{
  if(compiler == ON) {
    *heap++ = (Inst)&lit;
    *heap++ = (Inst)TOS; DROP;
  }
}


/******************************************************
 *|F| quote_super_class()
 *|F| Always invoke the quote.
 *|F|
 ******************************************************/
void quote_super_class()
{
  invoke();
}


/******************************************************
 *|F| quote_class()
 *|F| Handler for quotes; this takes two cells, one
 *|F| which is a call to this function, the other is
 *|F| the pointer to the quote to invoke.
 *|F|
 ******************************************************/
void quote_class()
{
  lit();
  invoke();
}


/******************************************************
 *|F| quote_macro_class()
 *|F| If compiling, invoke the quote. If interpreting,
 *|F| silently ignore it.
 *|F|
 ******************************************************/
void quote_macro_class()
{
  if(compiler == ON)
    invoke();
  else
    DROP;
}


/******************************************************
 *|F| quote_forth_class()
 *|F| Perform data_class() semantics, then, if 
 *|F| compiling, compile a call to invoke(). Otherwise,
 *|F| invoke() is called with the xt on TOS.
 *|F|
 ******************************************************/
void quote_forth_class()
{
  if(compiler == ON)
  {
    *heap++ = &quote_class;
    *heap++ = (Inst)TOS; DROP;
  }
  else
  {
    invoke();
  }
}
