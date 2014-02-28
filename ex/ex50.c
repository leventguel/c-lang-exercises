#include <math.h>
#include <stdio.h>

int main(void)
{

  float x, y, y1, x1, f;

  x = 12682.0;
  x1 = sqrt(x);
  y = x + 1.0;
  y1 = sqrt(y);
  
  f=2*(y1-x1);

  printf("%f %f %f %f \n", x, x1, y, y1);
  printf("%f %f %f \n", x, f, 2.0/(pow(x, 0.5)+pow(x, 0.5)));
  
  return 0;

}
