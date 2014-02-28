#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
  char *s;

  s = malloc(10 * sizeof *s);
  strcpy(s, "Jim");
  printf("s = %s\n", s);
  return 0;
}
