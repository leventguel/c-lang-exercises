#include <stdio.h>
 
int main(void)
{
  double a = 42;
  void *x = &a;
  void **y = &x;
 
  double **b = (double **) y;
 
  printf("**b: %f\n", **b);
 
  y = (void **) b;
 
  printf("**y: %f\n", **((double **) y));
  return 0;
}
