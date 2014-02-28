#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i;
  long double j, x, y, z;

  y = 1.0;
  x = -5.5;
  
  j = 1.0;

  printf( "      i           z/100000.0                  1/y \n\n" );

  for(i=1; i<=25; i++)
    {
      j *= i;
      z = floor( powl(-1.0, i) + ((powl(-x, i) *(100000.0/j))) + ((2.0/powl(((-x)*(-x)), 2.0*i)) *((2.0/100000.0)/(2.0/j))));
      y += ( z/100000.0 );

      printf( "      %d      %'.16Lf      %'.16Lf \n", i, z/100000.0, 1/y );

    }

  printf( "      real value of exp(-5.5) = %'.16Lf\n", (long double) exp(-5.5) );
  return 0;
}

