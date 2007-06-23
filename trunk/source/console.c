/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: console.c
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
extern long base;


/******************************************************
 *|G| .        ( n- )      Display the TOS
 *
 *|F| dot()
 *|F| Display the number on TOS using the current base
 *|F| if possible.
 *|F|
 ******************************************************/
void dot()
{
  switch(base)
  {
    case  8: printf("%lo ", TOS); break;
    case 16: printf("%lx ", TOS); break;
    default: printf("%li ", TOS); break;
  }
  DROP;
}


/******************************************************
 *|G| emit     ( c- )      Display the ASCII character
 *|G|                      for TOS
 *
 *|F| emit()
 *|F| Display the character TOS corresponds to. Consumes
 *|F| TOS.
 *|F|
 ******************************************************/
void emit()
{
  putchar((char)TOS);
  DROP;
}


/******************************************************
 *|G| type     ( a- )      Display a string
 *
 *|F| type()
 *|F| Display the string TOS points to. Consumes TOS.
 *|F|
 ******************************************************/
void type()
{
  printf((char *)TOS);
  DROP;
}


/******************************************************
 *|G| bye      ( - )       Quit Toka
 *
 *|F| bye()
 *|F| Quit Toka
 *|F|
 ******************************************************/
void bye()
{
  exit(0);
}
