#include <math.h>
#include <stdio.h>

int main()
{
  int num[]={10,20,30,40,50};
  print(&num, 5, num);
  return 0;
}

int print(int *j, int n, int b[5])
{
  int i;
  for(i=0; i<=4; i++)
    {
      printf("%lu %d %d %lu \n", (unsigned long int) &j[i], *j, *(b+i), (unsigned long int) &b);
      j++;
    }
  return 0;
}
