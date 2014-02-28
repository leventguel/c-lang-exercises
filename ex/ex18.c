#include <math.h>
#include <stdio.h>

int main()
{
  int num[]={10,20,30,40,50};
  int i, *j;

  j=num;
  for(i=0;i<=4;i++)
    {
      printf("%u %u %d %d\n", (unsigned int) &j, (unsigned int) (&j[i]), *j, num[i]);
      j++;
    }
}
