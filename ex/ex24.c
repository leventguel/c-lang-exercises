#include <math.h>
#include <stdio.h>

int main()
{
  int arr[6][3]={{11,12,13},{21,22,23},{31,32,33},{41,42,43},{51,52,53}};
  int i,j;
  
  int *p,(*q)[3],*r;

  p=(int*)arr;
  q=arr;
  r=(int*)q;

  printf("%lu %lu %d %d %d %d \n", (unsigned long int)  p, (unsigned long int) q, *p, *(r), *(r+1), *(r+2));
  p++;
  q++;
  
  r=(int*)q;

  printf("%lu %lu %d %d %d %d \n", (unsigned long int) p, (unsigned long int) q, *p, *(r), *(r+1), *(r+2));
  return 0;
}

