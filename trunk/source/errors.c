/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: errors.c
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
 *|F| error(long code)
 *|F| Display a given error by code
 *|F|
 ******************************************************/
void error(long code)
{
  printf("E%li: ", code);
  switch (code)
  {
    case ERROR_WORD_NOT_FOUND:
         printf("%s is not a word or a number.\n", (char *)TOS);
         DROP;
         break;
    case ERROR_NO_MEM:
         printf("Out of memory; aborting.\n");
         exit(1);
         break;
    case ERROR_FFI_ARGUMENTS:
         printf("Too many arguments to alien function.\n");
         break;
    case ERROR_FFI_LIBRARY_NOT_FOUND:
         printf("Unable to open library '%s'.\n", (char *)TOS);
         DROP;
         break;
    case ERROR_FFI_FUNCTION_NOT_FOUND:
         printf("Lookup of symbol '%s' failed.\n", (char *)TOS);
         DROP;
         break;
  }
}
