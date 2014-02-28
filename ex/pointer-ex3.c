#include <math.h>
#include <stdio.h>

int main()
{
  long int i,j,m[6], *k[6];

  char *course[3];

  course[0]="Numerical Methods";
  course[1]="and Programming";

  printf("%s %s\n", course[0], course[1]);

  for(i=0; i<5;i++) {m[i]=3*i;}
  k[0]=&m[1];
  *(k+3)=&*(m+4);
  j=k[3]-k[0];

  printf("%ld %ld %ld\n", j, *(k[0]+1), *k[3]);

  /*
    letter = course[0];
    for(i=0; i<5;i++)
    {
    j=letter-course[0];
    printf("%ld %c\n", j, *letter);
    letter++;
    }
  */
  return 0;
}
