#include <math.h>
#include <stdio.h>

int main(void)
{

  double x, y, y1, x1, f;

  x = 12682.0;
  x1 = sqrt(x);
  y = x + 1.0;
  y1 = sqrt(y);
  
  f=2*(y1-x1);

  printf("%f %e %e \n", x, f, 2/(y1+x1));

  
  return 0;

}
