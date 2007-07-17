/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: conditionals.c
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
 *|G| <        ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| less_than()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void less_than()
{
  NOS = (TOS <= NOS) ?  FALSE : TRUE; DROP;
}


/******************************************************
 *|G| >        ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| greater_than()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void greater_than()
{
  NOS = (TOS >= NOS) ?  FALSE : TRUE; DROP;
}


/******************************************************
 *|G| =        ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| equals()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void equals()
{
  NOS = (TOS != NOS) ? FALSE : TRUE; DROP;
}


/******************************************************
 *|G| <>       ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| not_equals()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void not_equals()
{
  NOS = (TOS == NOS) ? FALSE : TRUE; DROP;
}
