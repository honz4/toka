/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: dictionary.c
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
extern long stack[], sp;
extern long parser;


/******************************************************
 *|F| Variables:
 *|F|   ENTRY dictionary[4096];
 *|F|   Holds the dictionary entries, up to 4096
 *|F|
 *|F|   long last
 *|F|   A pointer to the most recent dictionary entry
 *|F|
 ******************************************************/
ENTRY dictionary[4096];
long  last=0;


/******************************************************
 *|F| add_entry(char *name, Inst xt, Inst class)
 *|F| Add an entry to the dictionary.
 *|F|
 ******************************************************/
void add_entry(char *name, void *xt, void *class)
{
  dictionary[last].xt = (Inst)xt;
  dictionary[last].class = (Inst)class;
  strcpy(dictionary[last].name, name);
  last++;
}


/******************************************************
 *|F| name_attach(void *class)
 *|F| Attach a name (from the input stream) to the 
 *|F| specified quote address. This word is given the
 *|F| semantics of the specified class.
 *|F|
 ******************************************************/
void name_attach(void *class)
{
  char *s;
  Inst xt;

  if (parser == TRUE)
  {
    s = gc_alloc(128, sizeof(char), GC_TEMP);
    get_token(s, 32); DROP;
  }
  else
  {
    s = (char *)TOS; DROP;
  }

  xt = (Inst)TOS; gc_keep(); DROP;
  add_entry(s, xt, class);
}


/******************************************************
 *|G| is       ( a"- )     Attach a name to a quote
 *|G|          ( a$- )     Non-parsing form
 *
 *|F| name_quote()
 *|F| Attach a name (from the input stream) to the 
 *|F| specified quote address. This word is given the
 *|F| semantics of quote_forth_class().
 *|F|
 ******************************************************/
void name_quote()
{
  name_attach(&quote_forth_class);
}


/******************************************************
 *|G| is-macro ( a"- )     Attach a name to a quote
 *|G|          ( a$- )     Non-parsing form
 *
 *|F| name_macro()
 *|F| Attach a name (from the input stream) to the 
 *|F| specified quote address. This word is given the
 *|F| semantics of quote_macro_class().
 *|F|
 ******************************************************/
void name_macro()
{
  name_attach(&quote_macro_class);
}


/******************************************************
 *|G| is-data  ( a"- )     Attach a name to data memory
 *|G|          ( a$- )     Non-parsing form
 *
 *|F| name_data()
 *|F| Attach a name (from the input stream) to the data
 *|F| at the specified address. Semantics are the same
 *|F| as the data_class().
 *|F|
 ******************************************************/
void name_data()
{
  name_attach(&data_class);
}


/******************************************************
 *|F| find_word()
 *|F| Search for a word (name taken from the string
 *|F| passed on TOS) in the dictionary. Returns the
 *|F| xt, class, and a flag of TRUE if found. If not
 *|F| found, returns only a flag of FALSE.
 *|F|
 ******************************************************/
void find_word()
{
  long flag, a;
  char *s = (char *)TOS; DROP;

  flag = 0;
  for (a = last-1; a >= 0; a--)
  {
    if ((strcmp(dictionary[a].name, s) == 0) && flag == FALSE) 
    {
      push((long)dictionary[a].xt);
      push((long)dictionary[a].class);
      flag = TRUE;
    }
  }
  push(flag);
}


/******************************************************
 *|G| `        ( "-a )     Return a quote corresponding
 *|G|                      to the specified word.
 *|G|          ( $-a )     Non-parsing form
 *
 *|F| return_quote()
 *|F| Find a name (from the input stream) and return a
 *|F| quote that corresponds to the word.
 *|F|
 ******************************************************/
void return_quote()
{
  long flag;
  Inst class, xt;

  char *s;

  if (parser == TRUE)
  {
    s = gc_alloc(128, sizeof(char), GC_TEMP);
    get_token(s, 32);
  }

  find_word();
  flag = TOS; DROP;

  if (flag == TRUE)
  {
    class = (Inst)TOS; DROP;
    xt = (Inst)TOS; DROP;
    if (class == &quote_macro_class)
      class = &quote_forth_class;
    if (class == &macro_class)
      class = &forth_class;
  }
  else
  {
    class = &data_class;
    xt = 0;
  }

  if (class != &quote_forth_class && class != &quote_macro_class)
  {
     begin_quote();
       push((long)xt);
       ((class)());
     end_quote();
  }
  else
  {
     push((long)xt);
     data_class();
  }
}
