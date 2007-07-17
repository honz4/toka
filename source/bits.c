/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: bits.c
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
 *|G| <<       ( ab-c )    Shift 'a' left by 'b' bits
 *
 *|F| lshift()
 *|F| Shift NOS left by TOS bits
 *|F|
 ******************************************************/
void lshift()
{
  NOS = NOS << TOS; DROP;
}


/******************************************************
 *|G| >>       ( ab-c )    Shift 'a' right by 'b' bits
 *
 *|F| rshift()
 *|F| Shift NOS right by TOS bits
 *|F|
 ******************************************************/
void rshift()
{
  NOS = NOS >> TOS; DROP;
}


/******************************************************
 *|G| and      ( ab-c )    Perform a bitwise AND
 *
 *|F| and()
 *|F| Perform a bitwise AND
 *|F|
 ******************************************************/
void and()
{
  NOS = TOS & NOS; DROP;
}


/******************************************************
 *|G| or       ( ab-c )    Perform a bitwise OR
 *
 *|F| or()
 *|F| Perform a bitwise OR
 *|F|
 ******************************************************/
void or()
{
  NOS = TOS | NOS; DROP;
}


/******************************************************
 *|G| xor      ( ab-c )    Perform a bitwise XOR
 *
 *|F| xor()
 *|F| Perform a bitwise XOR
 *|F|
 ******************************************************/
void xor()
{
  NOS = TOS ^ NOS; DROP;
}
