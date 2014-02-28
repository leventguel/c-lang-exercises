/* Pointer to a function and passing the pointer to a function */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define l 4

void cube(float);

void cube(x)
     float x;
{
  float z;
  z=x*x*x;
  printf("%f\n", z);
}

void myfunction(x,y,d,powerthree)
     float x; int y[2], *d; void (*powerthree)(float);
{
  float z;
  x=2*x;
  y[1]=3*y[1];
  y[2]=3*y[2];
  *d=*d+2;
  (*powerthree)(x);
}


int main(void)
{
  float b; int a[2], *c;

  void (*func_ptr)();
  void myfunction();

  c=(int*) malloc(l);

  b=10.0;

  *c=5;

  a[0]=1;a[1]=2;
  
  func_ptr=myfunction;
  
  printf("before function call %f %d %d %d\n", b, a[0], a[1], *c);

  (*func_ptr)(b,a,c,cube);

  printf("after  function call %f %d %d %d\n", b, a[0], a[1], *c);

  return 0;
}

