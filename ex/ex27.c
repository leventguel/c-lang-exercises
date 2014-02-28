/* Dynamic memory allocation */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define l 4

int main(void)
{
  static int *a, i, *p;
  static float *b, *c;

  a=(int*) malloc(l);
  
  for(i=0;i<l;i++)
    { *(a+i)=i;}

  for(i=0;i<l;i++)
    {
      printf(" a %d %d %d \n", i, *(a+i), (int) (a+i));
    }

  p=(int*) calloc(l,2);
 
  for(i=0;i<l;i++)
    { *(p+i)=i*2;}

  for(i=0;i<l;i++)
    {
      printf(" p %d %d %d %lu \n", i, *(p+i), (int) (p+i), sizeof(p));
    }

  b=malloc(l);
  
  for(i=0;i<l+2;i++)
    { *(b+i)=i*4.0;}

  for(i=0;i<l+2;i++)
    {
      printf(" b %d %f %d %lu \n", i, *(b+i), (int) (b+i), sizeof(b));
    }

  c=calloc(l,8);
  
  for(i=0;i<l;i++)
    { *(c+i)=i*4.0;}

  for(i=0;i<l+1;i++)
    {
      printf(" c %d %f %d %lu \n", i, *(c+i), (int) (c+i), sizeof(c));
    }

  for(i=l+1;i<l+2;i++)
    {
      printf(" b %d %f %d \n", i, *(b+i), (int) (b+i));
    }

  return 0;
}

