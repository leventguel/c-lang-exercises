/* underflow and overflow */

#include <math.h>
#include <stdio.h>

int main(void)
{
  int i;
  float n, x;
  
  n=1;
  
  for(i=0; i<=127;i++)
    {
      n=n*2.0;
      x=1.0/(n);
      /* %e is towards -, %E is towards + signum */
      printf("%d %e %E\n", i, x, n); /* default precision for %d is 1, default precision for %e/%E is ±6 *, default exponent digits for %e/%E is 2 */
    }
  return 0;
}

/* 10^0 == 10^(00) == +E00 */
/* 2.0 == +2*10^6 == 2.000000+E00 via %E */
/* 10^(-1) == 10^(-01) == -e01 */
/* 1.0/(2.0) == 1.000000+E00/2.000000+E00 == 0.5 (.10^(-6)) == 5*10^(-1)(.10^(-6)) == 5(.10^(-6))*10^(-1) == 5(.10^(-6))-e01 == 5.000000-e01 via %e */
