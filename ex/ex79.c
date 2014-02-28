#include <stdio.h>
#include <signal.h>

int main()
{
  char *s;

  s = NULL;

  printf("%d\n", s[0]);
  return 0;
}
