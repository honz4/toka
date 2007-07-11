/******************************************
 *|F|
 *|F| File: hexdump.c
 *|F|
 ******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/******************************************
 *|F| hexdump(char *buf, int len)
 *|F| Print the buffer to stdout in hex and
 *|F| (when printable) ASCII.
 *|F|
 ******************************************/
void hexdump(char *buf, int len)
{
  char tmp[16];
  int x = 0;
  int y = 0;

  printf("\n");

  for (x = 0; x < len; ++x)
  {
    tmp[x % 16] = buf[x];  // Make each char in to hex

    if ((x + 1) % 16 == 0)
    {
      for (y = 0; y < 16; ++y)
        printf("%02x ", tmp[y] & 0xff);

      for (y = 0; y < 16; ++y)
        printf("%c", isprint(tmp[y]) ? tmp[y] : '.');

      printf("\n");
    }
  }

  if ((x % 16) != 0)
  {
    for (y = 0; y < (x % 16); ++y)
      printf("%02x ", tmp[y] & 0xff);

    for (y = (x % 16); y < 16; ++y)
      printf("   ");

    for (y = 0; y < (x % 16); ++y)
      printf("%c", isprint(tmp[y]) ? tmp[y] : '.');
  }
  printf("\n");
}
