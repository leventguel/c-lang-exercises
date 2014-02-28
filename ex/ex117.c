#include <stdio.h>

int *fun()
{
  int k = 35;
  return &k;
}

int main(void)
{
  int *j;
  int *fun();

  j = fun();
  printf("%d \n", *j);
  printf("%d \n", *j);
  return 0;
}
