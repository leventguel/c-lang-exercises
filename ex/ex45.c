#include <math.h>
#include <stdio.h>

int main(void)
{
  int i, j, z;
  float x, y;

  x = 1.0;
  y = -0.5;
  
  j = 1;

  for(i=1; i<=10; i++)
    {
      j = j*i;
      z = floor(pow(-1.0, i) * pow(y, i) * 100000/j);
      x = x + z/100000.0;
      /*  y = y + z/100000.0; */
      
      printf("      %d      %f \n", i, x);
      /* printf("      %d      %f      %f \n", i, z/100000.0, 1.0/y); */
    }

  printf("      real value of exp(-0.5) = %f\n", exp(0.5));
  return 0;
}

