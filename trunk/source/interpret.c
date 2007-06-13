/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: interpret.c
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


extern Inst *heap;
extern long last;
extern ENTRY dictionary[];
extern long stack[], sp;


/******************************************************
 *|F| Variables:
 *|F|   long compiler
 *|F|   When set to FALSE, interpret; when set to TRUE, 
 *|F|   compile. This is checked by the various word
 *|F|   classes defined in class.c
 *|F|
 *|F|   char *scratch
 *|F|   Temporary holding area used by the parser and
 *|F|   other routines.
 *|F|
 *|F|   char *tib
 *|F|   Pointer to the text input buffer.
 *|F|
 *
 *|G| heap     ( -a )      Variable pointing to the top
 *|G|                      of the local heap
 *|G| compiler ( -a )      Variable holding the compiler
 *|G|                      state
 ******************************************************/
long   compiler=0;
char *scratch;
char *tib;


/******************************************************
 *|G| count    ( a-ac )    Return an address/count pair
 *|G|                      for a string
 *
 *|F| count()
 *|F| Perform strlen() on the string passed on TOS. This
 *|F| returns the string and the count on the stack. The
 *|F| count is increased by 1 to include the trailing 
 *|F| ASCII 0.
 *|F|
 ******************************************************/
void count()
{
  char *s = (char *)TOS;
  long length = strlen(s) + sizeof(char);
  push(length);
}


/******************************************************
 *|F| interpret()
 *|F| Accept and process input.
 *|F|
 ******************************************************/
void interpret()
{
  Inst class;
  long flag;

  scratch = calloc(1024, sizeof(char));

  while (1)
  {
    display_prompt();
    flag = FALSE; class = 0;
    fflush(stdout);
    vm_stack_check();
    get_token(scratch, 32);
    find_word();
    flag = TOS; DROP;
    if (flag == FALSE)
    {
      if (strlen(scratch) != 0)
      {
        push((long)scratch);
        to_number();
        flag = TOS; DROP;
        if (flag == TRUE)
          data_class();
        else
          error(ERROR_WORD_NOT_FOUND);
      }   
    }
    else
    {
      class = (Inst)TOS; DROP;
      ((class)());
    }
  }
}
