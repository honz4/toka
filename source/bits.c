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
extern Inst *heap, *ip;
extern long stack[], rstack[], sp, rsp;


/******************************************************
 *|G| <<       ( ab-c )    Shift 'b' left by 'a' bits
 *
 *|F| lshift()
 *|F| Shift TOS left by NOS bits
 *|F|
 ******************************************************/
void lshift()
{
  long a = TOS, b = NOS;
  DROP;
  TOS = a << b;
}


/******************************************************
 *|G| >>       ( ab-c )    Shift 'b' right by 'a' bits
 *
 *|F| rshift()
 *|F| Shift TOS right by NOS bits
 *|F|
 ******************************************************/
void rshift()
{
  long a = TOS, b = NOS;
  DROP;
  TOS = a >> b;
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
  long a = TOS, b = NOS;
  DROP;
  TOS = a & b;
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
  long a = TOS, b = NOS;
  DROP;
  TOS = a | b;
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
  long a = TOS, b = NOS;
  DROP;
  TOS = a ^ b;
}
