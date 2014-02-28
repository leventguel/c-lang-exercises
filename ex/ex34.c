#include <math.h>
#include <stdio.h>

int main(void)
{
  static float s, x, x1, s1;

  x = -1.0 + 1.7320;
  s = x*x + 2*x - 2.0;
  x1 = -1.0 - 1.7320;
  s1 = x1*x1 + 2*x1 - 2.0;

  printf("\n%f %f \n", x, s);
  printf("%f %f \n\n", x1, s1);

  printf("%F %F \n", x, s);
  printf("%F %F \n\n", x1, s1);

  printf("%g %g \n", x, s);
  printf("%g %g \n\n", x1, s1);

  printf("%G %G \n", x, s);
  printf("%G %G \n\n", x1, s1);

  printf("%a %a \n", x, s);
  printf("%a %a \n\n", x1, s1);

  printf("%A %A \n", x, s);
  printf("%A %A \n\n", x1, s1);

  printf("%e %e \n", x, s);
  printf("%e %e \n\n", x1, s1);

  printf("%E %E \n", x, s);
  printf("%E %E \n\n", x1, s1);
  
  return 0;

}
