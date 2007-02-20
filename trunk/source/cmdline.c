/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: cmdline.c
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
 *|F| Variables:
 *|F|   long arg_count
 *|F|   Holds the number of command line arguments
 *|F|
 *|F|   char *arg_list[12]
 *|F|   Holds the list of command line arguments. 
 *|F|
 ******************************************************/
long arg_count;
char *arg_list[12];


/******************************************************
 *|G| #args    (  -n )     Return the number of arguments
 *
 *|F| num_args()
 *|F| Return the number of arguments, not including the
 *|F| file names used to launch this program.
 *|F|
 ******************************************************/
void num_args()
{
  push(arg_count);
}


/******************************************************
 *|G| arglist  (  -a )     Return a pointer to the 
 *|G|                      argument list.
 *
 *|F| get_arg_list()
 *|F| Return the number of arguments, not including the
 *|F| file names used to launch this program.
 *|F|
 ******************************************************/
void get_arg_list()
{
  push((long)&arg_list);
}


/******************************************************
 *|F| build_arg_list(char *args[], long count)
 *|F| Copy pointers to the command line arguments to
 *|F| arg_list[]. Also sets arg_count.
 *|F|
 ******************************************************/
void build_arg_list(char *args[], long count)
{
  long a;
  if(count >= 2)
  {
    for(a = 0; a < count; a++)
       arg_list[a] = args[a+1];
    arg_count = count - 2;
  }
  else
  {
    arg_count = 0;
  }
}
