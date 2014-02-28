#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char *malloc();

int main(void)
{
  char *s;

  s = malloc(10);
  strcpy(s, "Jim");
  printf("s = %s\n", s);
  return 0;
}
