/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: limits.c
 *|F|
 *
 * This is used to obtain a few values that may need
 * adjusting in the standard bootstrap. At present it
 * is designed for 64-bit systems, some trimming can be
 * done for 32-bit targets.
 *
 * Eventually we should be able to provide 32-bit and
 * 64-bit versions of the bootstrap, and only install
 * the proper one. That will make developing portable
 * applications easier. Symbolic names will replace the
 * hard coded constants used now.
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
  printf("\n");
  printf("Toka - System / Compiler Details\n");
  printf("--------------------------------\n");
  printf("Word Size: %i\n", __WORDSIZE);
  printf("--------------------------------\n");
  printf("Data Types:\n");
  printf(" - long  =  %i bytes\n", sizeof(long));
  printf("   - MIN = %i\n", LONG_MIN);
  printf("   - MAX =  %i\n", LONG_MAX);
  printf(" - signed char = %i bytes\n", sizeof(char));
  printf("--------------------------------\n");
  printf("\n");
  return 0;
}
