/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: decompile.c
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
extern ENTRY dictionary[];
extern long last;


/******************************************************
 *|F| long resolve_name(Inst xt)
 *|F| Search for a name in the dictionary that corresponds
 *|F| to 'xt'. Display it if found, and return a flag.
 *|F|
 ******************************************************/
long resolve_name(Inst xt)
{
  long flag, a;

  flag = FALSE;
  for (a = last; a > 0; a--)
  {
     if (dictionary[a].xt == xt && flag == 0)
     {
       printf("%s ", dictionary[a].name);
       flag = TRUE;
     }
  }
  return flag;
}


/******************************************************
 *|F| decompile(Inst *xt)
 *|F| Decompile a quote and its children and display the
 *|F| result on the screen.
 *|F|
 ******************************************************/
void decompile(Inst *xt)
{
  Inst this;
  long flag;
  char *string;

  printf("[ ");

  while (1) {
    this = (Inst)*xt++;
    resolve_name(this);
    if (this == (Inst)0)
    {
      printf("] ");
      return;
    }
    if (this == &lit)
    {
      this = (Inst)*xt++;
      if (resolve_name(this) == FALSE)
        printf("%li ", (long)this);
    }
    if (this == &string_lit)
    {
      string = (char *)*xt++;
      putchar('"');
      putchar(' ');
      for (; *string; string++)
      {
        switch (*string)
        {
          case 27: printf("\\^"); break;
          case 10: printf("\\n"); break;
          case 13: printf("\\r"); break;
          case 92: printf("\\"); break;
          case 34: printf("\\\""); break;
          default: putchar(*string);
        }
      }
      putchar('"');
      putchar(' ');
    }
    if (this == &qlit)
    {
      this = (Inst)*xt++;
      decompile((Inst *)this);
    }
    if (this == &quote_class)
    {
      this = (Inst)*xt++;
      flag = resolve_name(this);
      if (flag == FALSE)
      {
        decompile((Inst *)this);
        printf("invoke ");
      }
    }
#ifndef NOFFI
    if (this == &ffi_invoke)
      printf("<ffi> ");
#endif
  }
}


/******************************************************
 *|G| :see     (  "- )     Decompile the specified quote
 *
 *|F| see()
 *|F| Decompile the quote on the stack.
 *|F|
 ******************************************************/
void see()
{
  decompile((Inst *)TOS);
  DROP;
  putchar('\n');
}
