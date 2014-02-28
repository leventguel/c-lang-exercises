#include <math.h>
#include <stdio.h>

int main()
{
  float x,y;
  long int i,j, k[5];

  char letter, course[]="Numerical Methods";

  printf("%c %s\n", course[6], course);
  printf("%c %s\n", course[6], &course[0]);

  for(i=0; i<5;i++) {k[i]=3*i;}
  j=*(k+2);

  printf("%ld %ld\n", k[2], j);
  return 0;
}
