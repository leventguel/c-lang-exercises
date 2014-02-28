/* hello.c -- The most famous program of them all ..
 */

#include <stdio.h>

int main(void) {
  unsigned char x = 40;
  unsigned char * xptr = 0;

  xptr = &x;

  printf("number is: %02d\n",256 + ((unsigned short) *xptr));
  return 0;
}
