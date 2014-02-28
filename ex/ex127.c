#include <stdio.h>

int main(void)
{
  int i;
  
  int apple;
  int birny;
  int toasty;

  int *q = &i;

  int p = sizeof  *q;

  printf("sizeof p is: %u \n", p);

  apple = sizeof q;

  birny = sizeof (int) * sizeof *q;

  toasty = sizeof (int) * sizeof q;

  printf("sizeof apple is: %u \n", apple);

  printf("sizeof birny is: %u \n", birny);

  printf("sizeof toasty is: %u \n", toasty);

  return 0;
}
