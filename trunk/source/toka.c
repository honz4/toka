/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: toka.c
 *|F|
 *
 * Copyright (C) 2007 Charles R. Childers
 * Distributed under the terms of the MIT/X11 License
 * (see doc/LICENSE for full terms)
 *
 ******************************************************/

/******************************************************
 * For rebuild:
 *
 * USES bits class cmdline conditionals console
 * USES data debug decompile dictionary ffi files
 * USES gc initial interpret math parser quotes
 * USES stack vm
 *
 * LINUX_LIBS dl
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <memory.h>

#include "toka.h"

extern long base, compiler, last, isp;
extern Inst *heap;
extern FILE *input[];
extern long stack[], sp;



/******************************************************
 *|F| main()
 *|F| The main entry point into Toka. Sets up the
 *|F| dictionary and calls interpret().
 *|F|
 ******************************************************/
int main(int argc, char *argv[])
{
  char *homedir = getenv("HOME");
  char *personal = "/.toka";
  char *custom;

  build_dictionary();
  build_arg_list(argv, (long)argc);

  isp = 0;
  input[isp] = stdin;

  if (argc >= 2)
    include_file(argv[1]);

  if (homedir)
  {
    custom = gc_alloc(strlen(homedir) + strlen(personal) + sizeof(char), sizeof(char), GC_TEMP);
    strcpy(custom, homedir);
    strcat(custom, personal);
    include_file(custom);
  }

  if (include_file("bootstrap.toka") == FALSE)
    include_file(BOOTSTRAP);

  if (argc == 1)
    printf("Toka Language\nCopyright (c) 2006-2007 Charles R. Childers\n\n");

  interpret();

  return 0;
}
