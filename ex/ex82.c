#include <stdio.h>

int main()
{
  double x;
  int y;
  int z;

  x = 4000.0;
  y = 20;
  z = -17;

  printf("%d %d %d\n", (int) x, y, z);
  printf("%f %d %d\n", x, y, z);
  printf("%lf %d %d\n", x, y, z);
  printf("%lf %lf %lf\n", x, (double) y, (double) z);
  return 0;
}
