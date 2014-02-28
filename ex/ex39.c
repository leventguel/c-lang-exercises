#include <math.h>
#include <stdio.h>

int main(void)
{
  int i;
  float x, y;

  x=1.0/6.0;

  i = ceil(x * 100 + .5);
  y = i / 100.0;

  printf("%d %f %f \n", i, x, y);
  return 0;
}
