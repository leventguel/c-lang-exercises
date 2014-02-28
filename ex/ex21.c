#include <math.h>
#include <stdio.h>

int main()
{
  static int arr[][2]={{11,12}, {21,22}, {31,32}, {41,42}, {51,52}};
  int i,j;
  
  arr[5][0]=61; arr[5][1]=62;

  for(i=0;i<=5;i++)
    {
      for(j=0;j<=1;j++)
	{
	  printf("%lu %lu %d %d %d \n", (unsigned long int) (arr[i]), (unsigned long int) (arr[i]+j), arr[i][j], *(*(arr+i)+j), *(arr[i]+j));
	}
    }
  return 0;
}
