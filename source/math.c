/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: math.c
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
 *|G| +        ( ab-c )    Add TOS and NOS
 *
 *|F| add()
 *|F| Add TOS to NOS
 *|F|
 ******************************************************/
void add()
{
  NOS += TOS; DROP;
}


/******************************************************
 *|G| -        ( ab-c )    Subtract TOS from NOS
 *
 *|F| subtract()
 *|F| Subtract TOS from NOS
 *|F|
 ******************************************************/
void subtract()
{
  NOS -= TOS; DROP;
}


/******************************************************
 *|G| *        ( ab-c )    Multiply TOS by NOS
 *
 *|F| multiply()
 *|F| Multiply TOS by NOS
 *|F|
 ******************************************************/
void multiply()
{
  NOS *= TOS; DROP;
}


/******************************************************
 *|G| /mod     ( ab-cd )   Divide and get remainder
 *
 *|F| divmod()
 *|F| Divide and return the result, including remainder
 *|F|
 ******************************************************/
void divmod()
{
  long a = TOS, b = NOS;
  NOS = b % a;
  TOS = b / a;
}
