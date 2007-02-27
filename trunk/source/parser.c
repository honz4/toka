/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: parser.c
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
#include <errno.h>
#include <ctype.h>
#include <memory.h>

#include "toka.h"
extern long stack[], sp;



/******************************************************
 *|F| Variables:
 *|F|   FILE *input[]
 *|F|   Current file stream to parse from. Setup as
 *|F|   an array of 8 inputs.
 *|F|
 *|F|   long isp
 *|F|   Pointer to the most recent input source in the array
 *|F|
 *|F|   long base
 *|F|   Holds the current numeric base
 *|F|
 *
 *|G| base     ( -a )      Variable containg the current
 *|G|                      numeric base
 ******************************************************/
FILE *input[8];
long base=10;
long isp=0;



/******************************************************
 *|G| >number  ( a-nf )    Attempt to convert a string
 *|G|                      to a number
 *
 *|F| to_number()
 *|F| Attempt to convert a string (on TOS) to a number.
 *|F| This accepts a format of:
 *|F|   [-]number
 *|F| If successful, it leaves the number and a flag of
 *|F| -1 on the stack. Otherwise, it leaves the original
 *|F| string, and a flag of 0.
 *|F|
 ******************************************************/
void to_number()
{
  char *s, *t;
  long flag;

  s = (char *)TOS; DROP;
  t = s;
  flag = -1;

  if (*t == '-')
    *t++;

  for(; *t; *t++)
  {
     if (base <= 10)
     {
       if (!isdigit(*t))
       {
         flag = 0;
         break;
       } 
     }
     else 
     {
       if (!isxdigit(*t))
       {
         flag = 0;
         break;
       } 
     }
  }

  if (flag == -1)
    push(strtol(s, (char **)NULL, base));
  else
     push((long)s);
  push(flag);
}



/******************************************************
 *|G| parse    ( d-a )     Parse until the character 
 *|G|                      represented by 'd' is found.
 *|G|                      Return a pointer to the string
 *
 *|F| parse()
 *|F| Parse the input buffer until the character passed
 *|F| on TOS is found, or until the end of the line is
 *|F| encountered. Return a pointer to the resulting
 *|F| string on the stack.
 *|F|
 ******************************************************/
void parse()
{
  long delim;
  char *s;

  delim = TOS; DROP;
  s = gc_alloc(1024, sizeof(char), GC_MEM);
  get_token(s, delim);
}



/******************************************************
 *|F| get_token(char *s, long delim)
 *|F| Return a string (in "s") up to the specified 
 *|F| delimiter or the end of the line. This also puts
 *|F| the resulting string on the stack.
 *|F|
 ******************************************************/
void get_token(char *s, long delim)
{
  char *t;
  long c;

  t = s;

  while (1)
  {
    if ((c = getc(input[isp])) == EOF)
    {
      fclose(input[isp]);
      isp--;
      break;
    }
    if (c == 10 || c == 13 || c == delim)
      break;
    if (c >= 32)
      *t++ = (char)c;
  }
  *t++ = 0;
  push((long)s);
}



/******************************************************
 *|F| include_file(char *s)
 *|F| Attempt to open a file ("s") and add it to the
 *|F| top of the input stack.
 *|F|
 ******************************************************/
void include_file(char *s)
{
  FILE *file;
  file = fopen(s, "r");
  if (file)
  {
    isp++;
    input[isp] = file;
  }
}



/******************************************************
 *|G| :include  ( $- )     Attempt to open a file and
 *|G|                      add it to the input stack.
 *
 *|F| include()
 *|F| Take a filename off the stack, attempt to open
 *|F| it and add it to the input stream if successful.
 *|F|
 ******************************************************/
void include()
{
  char *s;
  s = (char *)TOS; DROP;
  include_file(s);
}



/******************************************************
 *|G| :needs    ( $- )     Attempt to include a file
 *|G|                      from the library (normally
 *|G|                      /usr/share/toka/library)
 *
 *|F| needs()
 *|F| Take a filename off the stack. Attempt to open it
 *|F| from the library, and add it to the input stream 
 *|F| if successful.
 *|F|
 ******************************************************/
void needs()
{
  char *s;
  char *d;

  d = gc_alloc(384, sizeof(char), GC_TEMP);

  strcpy(d, LIBRARY);
  s = (char *)TOS; DROP;
  strcat(d, s);

  include_file(d);
}
