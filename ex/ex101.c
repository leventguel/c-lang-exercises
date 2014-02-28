#include <stdio.h>

int main(void) {
  if ( -1 < (unsigned char) 1 )
    printf("-1 is less than (unsigned char) 1: ANSI semantics ");
  else
    printf("-1 NOT less than (unsigned char) 1: K&R semantics ");
  printf("\n");
  return 0;
}
