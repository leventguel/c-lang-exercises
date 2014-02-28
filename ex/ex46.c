#include <math.h>
#include <stdio.h>

int main(void)
{
  int i, j, z;
  float x, y;

  y = 1.0;
  x = -5.5;
  
  j = 1;

  for(i=1; i<=14; i++)
    {
      j = j*i;
      z = floor(pow(-1.0, i) * pow(x, i) * 100000/j);
      y = y + z/100000.0;
      /*  y = y + z/100000.0; */
      
      printf("      %d      %f      %f \n", i, z/100000.0, 1.0/y);
      /* printf("      %d      %f      %f \n", i, z/100000.0, 1.0/y); */
    }

  printf("      real value of exp(-5.5) = %f\n", exp(-5.5));
  return 0;
}

