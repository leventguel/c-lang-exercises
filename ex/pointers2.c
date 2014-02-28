#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *s;

  s = malloc(10 * sizeof *s);
  strcpy(s, "Jim");
  printf("s = %s\n", s);
  return 0;
}
