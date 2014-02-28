#include <stdio.h>

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int main(void)
{
  int a = 5, b = 7;
  printf("before swap: %d %d \n", a, b);
  swap(&a, &b);
  printf("after swap: %d %d \n", a, b);
  return 0;
}
