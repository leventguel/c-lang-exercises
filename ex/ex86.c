#include <stdio.h>

int main(void)
{
  int xx;
  for(xx = 5;xx < 15;xx = xx + 1){
    if (xx == 8)
      break;
    printf("in the break loop, xx is now %d\n",xx);
  }
  for(xx = 5;xx < 15;xx = xx + 1){
    if (xx == 8)
      continue;
    printf("In the continue loop, xx is the now %d\n",xx);
  }
  return 0;
}
