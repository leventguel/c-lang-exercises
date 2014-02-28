/* Argument passing */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define l 4

int main(void)
{
  float b; int a[2], *c;

  void myfunction();

  c=(int*) malloc(l);

  b=10.0;

  *c=5;

  a[0]=1;a[1]=2;

  printf("before function call %f %d %d %d \n", b, a[0], a[1], *c);

  myfunction(b,a,c);

  printf("after  function call %f %d %d %d \n", b, a[0], a[1], *c);

  return 0;
}

void myfunction(x,y,d)
     float x; int y[2], *d;
{
  float z;
  x=2*x;
  y[1]=3*y[1];
  y[2]=3*y[2];
  *d=*d+2;

}
