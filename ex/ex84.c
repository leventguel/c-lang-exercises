#include <stdio.h>

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


int main(void)
{
  scanf("%llF", &val);
  printf("%.0llF! = %.0llF \n", val, fact(val));
  printf("\n");
  return 0;
}
