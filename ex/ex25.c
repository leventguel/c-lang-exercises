#include <math.h>
#include <stdio.h>

int main()
{
  int arr[6][2]={{11,12},{21,22},{31,32},{41,42},{51,52}};
  int i,m,n,*j;
  m=5;
  n=2;
  print(arr,m,n); /* array to array */
  show(arr,m,n); /* array to pointer */
  display(arr,m); /* array to 1 dim array of pointers */
  exhibit(arr,m); /* array to 2 dim array of pointers */
  return 0;
}

int print(int b[6][2], int l, int p)
{
  int i, j;
  printf("print \n");
  for(i=0; i<l; i++)
    {
      printf("           ""%d %d \n", b[i][0], b[i][1]);
    }
  return 0;
}

int show(int *b, int l, int p)
{
  int i, j;
  printf("show \n");
  for(i=0; i<l; i++)
    {
      printf("           ""%d %d \n", *(b+i*2+0), *(b+i*2+1));
    }
  return 0;
}

int display(int (*b)[2], int l)
{
  int i, j, *p;
  printf("display \n");
  for(i=0; i<l; i++)
    {
      p=(int*)b;
      printf("           ""%d %d \n", *(p), *(p+1));
      b++;
    }
  return 0;
}

int exhibit(int (*b)[5][2], int l)
{
  int i, j;
  printf("exhibit \n");
  for(i=0; i<l; i++)
    {
      printf("           ""%d %d \n", (*b)[i][0], (*b)[i][1]);
    }
  return 0;
}
