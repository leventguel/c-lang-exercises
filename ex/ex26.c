#include <math.h>
#include <stdio.h>

#define l 4

int main()
{
  int *a, i;
  int *matrix1();
  int(*b)[2];
  int *r;
  int(*matrix2())[2];
  int(*c)[5][2];
  int(*matrix3())[5][2];
  

  a=matrix1();
  printf("matrix1: \n");
  for(i=0; i<=l;i++)
    {
      printf("\t%d %d \n", *(a+i*2+0), *(a+i*2+1));
    }
  
  b=matrix2();
  printf("matrix2: \n");
  for(i=0; i<=l;i++)
    {
      r=(int*)b;
      r=(int*)b;
      b++;
      printf("\t%d %d \n", *r, *(r+1));
    }

  c=matrix3();
  printf("matrix3: \n");
  for(i=0;i<=l;i++)
    {
      printf("\t%d %d \n", (*c)[i][0], (*c)[i][1]);
    }
  return 0;
}

int (*matrix1())
{
  static int arr[][2]={{11,12},{21,22},{31,32},{41,42},{51,52}};
  return *arr;
}

int (*matrix2())[2]
{
    static int arr[][2]={{11,12},{21,22},{31,32},{41,42},{51,52}};
    return arr;
}

int (*matrix3())[5][2]
{
    static int arr[][2]={{11,12},{21,22},{31,32},{41,42},{51,52}};
    return (int (*)[5][2]) arr;
}
