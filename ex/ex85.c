#include <stdio.h>
#include <stdlib.h>

int i;
long double n;
long double val;
long double acc=1;

long double fac_aux(long double n, long double acc)
{
  return n < 1 ? acc : fac_aux(n-1, n*acc);
}

long double fact(long double n)
{
  return fac_aux(n, acc);
}


int main(int argc, char **argv)
{

  if(argc < 2) {
    while(scanf("%LF", &val) == 1) printf("%.0LF! = %.0LF \n", val, fact(val));
  }
  else
    {
      for(i=1; i < argc; i++)
	printf("%.0LF! = %.0LF \n", (long double) atoi(argv[i]), fact( (long double) (atoi(argv[i])) ) );
    }
  
  printf("\n");
  return 0;
}
