#include <stdio.h>

void increment()
{
  static int i=1;
  printf("%d \n", i);
  i += 1;
}

int main(void)
{
  increment();
  increment();
  increment();
  return 0;
}
