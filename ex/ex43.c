#include <math.h>
#include <stdio.h>

int main(void)
{
  int i;
  double x; double y;

  x=1.0/6.0;

  i = floor(x * 100);
  y = i / 100.0;

  printf("%d %'.7f %'.7f %'.7lf\n", i, x, y, y * 6.0);
  return 0;
}
