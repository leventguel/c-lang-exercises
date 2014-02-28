#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
  int *i;

  i = (int *) 16383;

  printf("%d\n", *i);
  return 0;
}
