/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: prompt.c
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
#include <ctype.h>
#include <memory.h>

#include "toka.h"
extern long compiler, parse_ended;
extern long stack[], rstack[], sp, rsp;
extern FILE *input[];
extern long isp;


/******************************************************
 *|F| Variables:
 *|F|   long prompt
 *|F|   Variable that determines whether or not to
 *|F|   display the prompt.
 *|F|
 *|G| prompt   ( -a )      prompt display variable
 ******************************************************/
long prompt = FALSE;


/******************************************************
 *|F| display_prompt()
 *|F| Display the prompt if 'prompt' variable is TRUE
 *|F|
 ******************************************************/
void display_prompt()
{
  long a;

  if ((prompt == TRUE) && (compiler == FALSE) && (parse_ended == TRUE) && (input[isp] == stdin))
  { 
   if (sp > 0)
   {
     printf("| ");
     for (a = 1; a <= sp; a++)
      {
        push(stack[a]);
        dot();
      }
   } 
   printf("> ");
  }
}
