#include <math.h>
#include <stdio.h>

int main(void)
{
  int i;
  float j, x, y, z;

  y = 1.0;
  x = -5.5;
  
  j = 1.0;

  printf("      i               z                      y \n");

  for(i=1; i<=25; i++)
    {
      j *= i;
      z = floor((pow(-1.0, i) + pow(-x, i))/j * 100000.0);
      y += (z/100000.0);

      printf("      %d      %'.6lf      %'.6lf \n", i, z/100000.0, 1.0/y);

    }

  printf("      real value of exp(-5.5) = %f\n", exp(-5.5));
  return 0;
}

