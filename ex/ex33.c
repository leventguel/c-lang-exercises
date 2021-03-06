/* Maximum value of integer */

#include <math.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
  printf("\nchar_min: %d \n", CHAR_MIN);
  printf("char_max: %d \n", CHAR_MAX);
  printf("char_bit: %d \n\n", CHAR_BIT);
  printf("size of short int: %lu\nbits in short int: %lu\n\n", sizeof(short int), sizeof(short int)*CHAR_BIT);
  short int i;
  short int n, sum, m;
  short int bits=sizeof(short int)*CHAR_BIT;
  n=-1;

  for(i=1; i<=bits+1;i++)
    {
      n=n*2;
      printf("%d %d %d\n", i, n, -n);
    }

  m=1;
  sum=1;
  
  for(i=1; i<=bits-2;i++)
    {
      m=m*2;
      sum=sum+m;
    }

  printf("%d %d \n", sum, sum+1);

  m=-1;
  sum=-1;
  
  for(i=1; i<=bits-2;i++)
    {
      m=m*2;
      sum=sum+m;
    }

  printf("%d %d\n", sum, sum-1);

  /* all zero is used to store the extra negative number */

  return 0;
}
