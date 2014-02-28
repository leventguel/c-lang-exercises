#include <math.h>
#include <stdio.h>

int main(void)
{
  int i;
  float x, y;

  x=.534085734;

  i = floor(x * 100000 + .5);
  y = i / 100000.0;

  printf("%d %f %f \n", i, x, y);
  return 0;
}
